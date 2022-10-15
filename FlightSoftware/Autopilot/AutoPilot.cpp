#include "AutoPilot.h"
#include <iostream>
#include <fstream>
#include "ControlConsts.h"
#include <string>

AutoPilot::AutoPilot() 
{
	double J = 0.05;
	
	Reset();
	myDrone_.mass = 1;
	myDrone_.J_motor = 0.01;

	myGuidance_.accel_cmd << 0, 0, 4;
	myGuidance_.v_cmd << 0, 0,0;
	myGuidance_.yawCmd = 0;
	inTrackAccel_ = 0;
	inTackAccelCmd_ = 0;

	xTrackAccel_ = 0;
	xTrackAccelCmd_ = 0;
	yawCmdLast = 0;

	mode = StateTypes::AP_WAIT;
	newApCmdRdy_ = false;
	guideInit = false;
	stateInit = false;
	apInit = false;
	RunUpComplete = false;
	
	Reset();

#ifdef DEBUG_DATA
	SetupDebug();
#endif
}




AutoPilot::~AutoPilot()
{
#ifdef DEBUG_DATA
	fclose(debugFp);
#endif
}


void AutoPilot::Reset()
{
	pitchIntegrator.Reset();
	rollIntegrator.Reset();
	yawIntegrator.Reset();
	ThrottleAccum = RunUpThrottle0;
}


void AutoPilot::setInput(FullState *in)
{
	double q1, q2, q3, q4;
	myState_ = *in;
	q1 = myState_.q[0];
	q2 = myState_.q[1];
	q3 = myState_.q[2];
	q4 = myState_.q[3];


	w1 = myState_.omega(0);
	w2 = myState_.omega(1);
	w3 = myState_.omega(2);
	
	yaw = atan2(-2*(q1*q2 - q3*q4),  ( 1 - 2*q1*q1 - 2*q3*q3) );
	
	if (!stateInit)
	{
		yawLast = yaw;
		stateInit = true;
	}
	operate();
}

void AutoPilot::operate()
{

	switch (mode)
	{
	case StateTypes::AP_WAIT:
		CheckInit();
		break;
	case StateTypes::AP_SPINUP:
		SpinUp();

		break;
	case StateTypes::AP_STANDBY:
		SpinIdle();
		break;
	case StateTypes::AP_CMD:
		Iterate();
		break;
	}

}
void AutoPilot::setInput(GuidanceCmd *in)
{
	myGuidance_ = *in;
	yawCmd = in->yawCmd;
	if (in->reset)
	{
		Reset();
		yawCmdLast = yawCmd;
	}
	if (!guideInit)
	{
		yawCmdLast = yawCmd;
		guideInit = true;
	}
	if (!apInit)
	{
		CheckInit();
	}

}

void AutoPilot::setInput( DroneProperties *in ) 
{
	myDrone_ = *in;

}
bool AutoPilot::getOutput(BladeCmd *out)
{
	if( newApCmdRdy_ )
	{
		out->rate1 = myCmd_.rate1;
		out->rate2 = myCmd_.rate2;
		out->rate3 = myCmd_.rate3;
		out->rate4 = myCmd_.rate4; 
		newApCmdRdy_ = false;
		return true;
	}
	return false;
}

bool AutoPilot::getOutput(AutopilotReport *out)
{
	if (sendReport)
	{
		sendReport = false;
		out->mode = mode;
		return true;
	}
	return false;
}

void AutoPilot::getCommand( GuidanceCmd *out )
{
	*out = myGuidance_;
	
}

/*void AutoPilot::getQuat( double *qq )
{
	qq[0] = q_err3(0);
	qq[1] = q_err3(1);
	qq[2] = q_err3(2);

}*/




void AutoPilot::Iterate()
{

	// Properties stuff
	dT_ = 0.01;
	
	//std::cout << m2w << std::endl;
	accelFrameChange();
	// 
	scheduleGains();
	// Run APS
	runPitchAp();
	runRollAp();
	runYawAp();
	//
	
	// Calculate the throttle command (btwn 0-1 , percentage!) 
	throttleCmd = sqrt( accelCmdTrack_.dot(accelCmdTrack_)) * AccelToThrottle; 
	throttleCmd = Saturate(throttleCmd, 0, 1);

	convertToCommands();

}


void AutoPilot::getR( double *R)
{
	R[0] = myCmd_.rate1;
	R[1] = myCmd_.rate2;
	R[2] = myCmd_.rate3;
	R[3] =myCmd_.rate4;
}

void AutoPilot::getM( double *M)
{
	M[0] = M1Cmd_;
	M[1] = M2Cmd_;
	M[2] = M3Cmd_;
}


void AutoPilot::runPitchAp()
{
	double accelError;
	double intTerm;
	double intIn;
	double out;
	accelError = inTackAccelCmd_ - inTrackAccel_;
	intIn = accelError*KaPitch_ + w2*KsynPitch_;
	intTerm = pitchIntegrator.Integrate(intIn, dT_);
	M2Cmd_ =( KwPitch_*w2 + intTerm);
}
void AutoPilot::runRollAp()
{
	double accelError;
	double intTerm;
	double intIn;
	double out;
	accelError = xTrackAccelCmd_ - xTrackAccel_;
	intIn = accelError*KaRoll_ + w1*KsynRoll_;
	intTerm = rollIntegrator.Integrate(intIn, dT_);
	M1Cmd_ = KwRoll_*w1 + intTerm;

}
void AutoPilot::runYawAp()
{
	double intTerm;
	double intIn;
	
	
	intIn = yawError*KaYaw_ + w3*KsynYaw_;
	intTerm = yawIntegrator.Integrate(intIn, dT_);
	M3Cmd_ =( KwYaw_*w3 + intTerm);

	
	yawLast = yaw;
	yawCmdLast =  yawCmd;

	
}



void AutoPilot::accelFrameChange()
{
	// DCM local to track
	Eigen::Vector3d tmp;
	double vAng;
	
	ConstrainYawError();
	vAng = yawCmd;
	dcmLocalToTrack_ << cos(vAng), sin(vAng), 0,
		-sin(vAng), cos(vAng), 0,
		0, 0, 1;


	dcmCToB_ = quatToDcm(myState_.q);
	//


	dcmBToTrack_ = dcmLocalToTrack_ * dcmCToB_.transpose();


	tmp = (dcmCToB_.transpose()) * myState_.accel;

	accelTrack_ = dcmBToTrack_ * myState_.accel;
	accelCmdTrack_ = dcmLocalToTrack_ * myGuidance_.accel_cmd;

	inTrackAccel_ =  accelTrack_(0);
	inTackAccelCmd_ = accelCmdTrack_(0);

	xTrackAccel_ = accelTrack_(1);
	xTrackAccelCmd_ = accelCmdTrack_(1);

	
	
}

void AutoPilot::scheduleGains()
{
	double acmd;
	acmd = (myGuidance_.accel_cmd.norm());
	if (acmd == 0)
	{
		KaRoll_ = 0;
		KaYaw_ = 0;
		KaPitch_ = 0;
	}
	else
	{
		KaRoll_ = KaR/acmd;
		KaYaw_ = KaY/acmd;
		KaPitch_ = KaQ / acmd;
	}





}


void AutoPilot::setGains(ApGain roll, ApGain pitch, ApGain yaw   )
{
	
	KaQ = pitch.Ka;
	KaR = roll.Ka;
	KaY = yaw.Ka;
	KsynPitch_ = pitch.Ksyn;
	KsynRoll_ = roll.Ksyn;
	KsynYaw_ = yaw.Ksyn;
	KwPitch_ =pitch.Kw;
	KwRoll_ = roll.Kw;
	KwYaw_ = yaw.Kw;


}

void AutoPilot::setSpinUp(double spinUpDelta,  double spinUp0)
{
	RunUpThrottle0 = spinUp0;
	RunUpThrottleDelta = spinUpDelta;
	ThrottleAccum = spinUp0;
}

Eigen::Matrix3d AutoPilot::quatToDcm(const Eigen::Vector4d &q)
{
	Eigen::Matrix3d out;
	
	double q1, q2, q3, q4 ,qnorm;
	double C11, C12, C13, C21, C22, C23, C31, C32, C33;
	qnorm = sqrt(q(0)*q(0) + q(1)*q(1) + q(2)*q(2) + q(3)*q(3));
	q1 = q(0) / qnorm;
	q2 = q(1) / qnorm;
	q3 = q(2) / qnorm;
	q4 = q(3) / qnorm;

	C11 = 1 - (2 * q2*q2) - (2 * q3*q3);
	C12 = 2 * (q1*q2 - q3*q4);
	C13 = 2 * (q3*q1 + q2*q4);
	C21 = 2 * (q1*q2 + q3*q4);
	C22 = 1 - (2 * q1*q1) - (2 * q3*q3);
	C23 = 2 * (q3*q2 - q1*q4);
	C31 = 2 * (q1*q3 - q2*q4);
	C32 = 2 * (q3*q2 + q1*q4);
	C33 = 1 - (2 * q1*q1) - (2 * q2*q2);

	out << C11, C12, C13,
		C21, C22, C23,
		C31, C32, C33;
	return out.transpose();
}

void AutoPilot::CheckInit()
{

	if (guideInit &&	stateInit)
	{
		apInit = true;
		sendReport = true;
		mode = StateTypes::AP_SPINUP;
		std::cout << "Autopilot Spinup" << std::endl;
		SpinUp();
	}

}

void AutoPilot::ConstrainYawError()
{
	
	yawCmd = unwrap(yawCmdLast, yawCmd);
	yaw = unwrap(yawLast, yaw);
	yawError = yawCmd - yaw;
	yawError = Saturate(yawError, -ControlConsts::YawErrorLim, ControlConsts::YawErrorLim);
	
}

void AutoPilot::SpinUp()
{
	double accel;
	
	accel = sqrt(myState_.accel.dot(myState_.accel));
	if ((accel < myGuidance_.accel_cmd[2] ))
	{
		ThrottleAccum += RunUpThrottleDelta;
	}
	else
	{
		RunUpComplete = true;
		sendReport = true;
		mode = StateTypes::AP_STANDBY;
		std::cout << "Autopilot Standby" << std::endl;
		AccelToThrottle = ThrottleAccum / accel; // Calculate the slope
		
	}

	RunUpComplete = true;
	sendReport = true;
	mode = StateTypes::AP_STANDBY;
	AccelToThrottle = 0.0126;

	M1Cmd_ = 0.0;
	M2Cmd_ = 0.0;
	M3Cmd_ = 0.0;
	
	throttleCmd = ThrottleAccum;
	throttleCmd = Saturate(throttleCmd, 0, 1);
	convertToCommands();

}

void AutoPilot::SpinIdle()
{
	M1Cmd_ = 0.0;
	M2Cmd_ = 0.0;
	M3Cmd_ = 0.0;

	throttleCmd =  sqrt(myGuidance_.accel_cmd.dot(myGuidance_.accel_cmd)) * AccelToThrottle;
	throttleCmd = Saturate(throttleCmd, 0, 1);
	convertToCommands();

	if (myGuidance_.runAp)
	{
		
		sendReport = true;
		mode = StateTypes::AP_CMD;
		std::cout << "Autopilot Full" << std::endl;
	}

}

void AutoPilot::convertToCommands()
{
	double J;
	// vector math stuff
	Eigen::MatrixXd m2w(4, 4);
	Eigen::MatrixXd w2m(4, 4);
	Eigen::VectorXd m(4);
	Eigen::VectorXd w(3);
	J = myDrone_.J_motor;
	/*w2m << 1, 1, -1, -1,
		-1, 1, 1, -1,
		1, 1, 1, 1,
		0.25, -0.25, 0.25, -0.25;*/
	w2m << .5, .5, -.5, -.5,
		-.5, .5, .5, -.5,
		1, 1, 1, 1,
		0.25, -0.25, 0.25, -0.25;
	m2w = w2m.inverse();
	m << AccelToThrottle*M1Cmd_, AccelToThrottle*M2Cmd_, AccelToThrottle*M3Cmd_, throttleCmd;
	w = (m2w)*m;
	myCmd_.rate1 = w(0);
	myCmd_.rate2 = w(1);
	myCmd_.rate3 = w(2);
	myCmd_.rate4 = w(3);
	newApCmdRdy_ = true;

#ifdef DEBUG_DATA	
	PrintDebug();
#endif

}

void AutoPilot::SetupDebug()
{


	
	debug.push_back(new DebugInfo("Rate1Ap", &myCmd_.rate1));
	debug.push_back(new DebugInfo("Rate2Ap", &myCmd_.rate2));
	debug.push_back(new DebugInfo("Rate3Ap", &myCmd_.rate3));
	debug.push_back(new DebugInfo("Rate4Ap", &myCmd_.rate4));
	
	debug.push_back(new DebugInfo("M1Ap", &M1Cmd_));
	debug.push_back(new DebugInfo("M2Ap", &M2Cmd_));
	debug.push_back(new DebugInfo("M3Ap", &M3Cmd_));
	debug.push_back(new DebugInfo("FAp", &myGuidance_.accel_cmd[2]));
	
	debug.push_back(new DebugInfo("Atrack0Ap", &accelTrack_[0]));
	debug.push_back(new DebugInfo("Atrack1Ap", &accelTrack_[1]));
	debug.push_back(new DebugInfo("Atrack2Ap", &accelTrack_[2]));

	debug.push_back(new DebugInfo("ACmdTrack0Ap", &accelCmdTrack_[0]));
	debug.push_back(new DebugInfo("ACmdTrack1Ap", &accelCmdTrack_[1]));
	debug.push_back(new DebugInfo("ACmdTrack2Ap", &accelCmdTrack_[2]));

	debug.push_back(new DebugInfo("KRAp", &KaRoll_));
	debug.push_back(new DebugInfo("KYAp", &KaYaw_));
	debug.push_back(new DebugInfo("KPAp", &KaPitch_));

	debug.push_back(new DebugInfo("yawAp", &yaw));
	debug.push_back(new DebugInfo("yawCmdAp", &yawCmd));
	debug.push_back(new DebugInfo("yawErrAp", &yawError));

	debug.push_back(new DebugInfo("throttleCmdAp", &throttleCmd));

	debug.push_back(new DebugInfo("KaPitchAp", &KaPitch_));
	debug.push_back(new DebugInfo("KaRollAp", &KaRoll_));
	debug.push_back(new DebugInfo("KaYawAp", &KaYaw_));


	debug.push_back(new DebugInfo("xTrackAccelCmdAp", &xTrackAccelCmd_));
	debug.push_back(new DebugInfo("xTrackAccelAp", &xTrackAccel_));
	debug.push_back(new DebugInfo("w1Ap", &w1));

	debug.push_back(new DebugInfo("inTrackAccelCmdAp", &inTackAccelCmd_));
	debug.push_back(new DebugInfo("inTrackAccelAp", &inTrackAccel_));
	debug.push_back(new DebugInfo("w2Ap", &w2));
	debugFp = fopen("AutopilotDebug.dat", "w");

	for (int k = 0; k < debug.size(); k++)
	{
		fprintf(debugFp, "%s,", debug.at(k)->title.c_str());
	}
	fprintf(debugFp,"\n");
}

void AutoPilot::PrintDebug()
{
	for (int k = 0; k < debug.size(); k++)
	{
		fprintf(debugFp, "%f,", *(debug.at(k)->data));
	}
	fprintf(debugFp, "\n");
}