#include "Guidance.h"
#include "LookupTable.h"
#include "ControlConsts.h"
#include <errno.h>




Guidance::Guidance()
{
	

		myLastState.time = -0.02;
	myState.time = -0.01;
	newCmdReady = false;
	myGuideCmd.reset = false;
	myGuideCmd.runAp = false;
	yawCmd = 0;
	guideMode = StateTypes::NONE;
	stateCount = 0;
	StatePerCmd = 10;
#ifdef DEBUG_DATA
	debugFp = fopen("GuidanceDebug.dat","w");
	fprintf(debugFp, " Xerr , Yerr , Zerr , Xaccel , Yaccel , Zaccel , acurveX, acurveY\n");
#endif
}


Guidance::~Guidance()
{
#ifdef DEBUG_DATA
	fclose(debugFp);
#endif
}


void Guidance::setGains(PidGain X, PidGain Y, PidGain H)
{
	posX.SetCoef(X.Kp, X.Ki, 0);
	posY.SetCoef(Y.Kp, Y.Ki, 0);
	posH.SetCoef(H.Kp,H.Ki, 0);

	GainX = X;
	GainY = Y;
	GainH = H;
}

void Guidance::setDownsample(double downSample)
{
	StatePerCmd = downSample;
}


void Guidance::Reset()
{
	posX.Reset();
	posY.Reset();
	posH.Reset();
}

void Guidance::LoadTrajectory(std::string fname)
{
	FILE *fp;
	fp = fopen(fname.c_str(), "rb");
	Trajectory tmp;
	if( fp == NULL ) 
	{
		fputs ("File error",stderr); 
		std::cout<<std::endl<<strerror(errno)<<std::endl;
		exit (1);
	}
	fread( &tmp , sizeof(Trajectory), 1 ,fp);
	while( !feof(fp) )
	{
		xTable.push_back( tmp.r[0] ) ; 
		yTable.push_back( tmp.r[1] ) ;
		hTable.push_back( tmp.r[2] ) ;
	
		vxTable.push_back( tmp.v[0] );
		vyTable.push_back( tmp.v[1] );
		tTable.push_back( tmp.time );

		//std::cout<<" x: "<< xTable.back() 
		//	<<" y: "<< yTable.back()
		//	<<" h: "<< hTable.back()
		//	<<" v1: "<<vxTable.back()
		//	<<" v2: "<<vyTable.back()<<std::endl;
		fread( &tmp , sizeof(Trajectory), 1 ,fp);
	}

	xTraj.Load( &tTable[0] , &xTable[0] , xTable.size() );
	yTraj.Load( &tTable[0] , &yTable[0] , yTable.size() );
	hTraj.Load( &tTable[0] , &hTable[0] , hTable.size() );
	vxTraj.Load( &tTable[0] , &vxTable[0] , vxTable.size() );
	vyTraj.Load( &tTable[0] , &vyTable[0] , vyTable.size() );

}

void Guidance::setInput(FullState *state)
{

	// Buffer up the last two states
	myLastState2 = myLastState;
	myLastState = myState;
	myState = *state;
	if (guideMode == StateTypes::NONE )
	{
		GroundSpinUp();
	}
	else
	{
		if ((stateCount % StatePerCmd) == 0)
		{

			populateCommandState();
			
		}
		stateCount++;
	}
}
void Guidance::setInput(StabilityCmd *cmd )
{
	//myGuideCmd.reset = true;
	stabilityCmd = cmd->stabilityPos;
	guideMode = StateTypes::HOLDPOINT;
	//Reset();
}
void Guidance::setInput(ReturnToBase *cmd)
{
	//TODO: This needs to do to things
	//	1) skew towward base
	//  2) fly there....since this is bank to turn skew has to happen first
	double tLine;
	//myGuideCmd.reset = true;
	

	/*guideMode = StateTypes::HOLDPOINT;
	stabilityCmd[0] = myState.pos[0];
	stabilityCmd[1] = myState.pos[1];;
	stabilityCmd[2] = myState.pos[2];;*/
	guideMode = StateTypes::LINE;
	myLine.lineStart << myState.pos;
	myLine.lineEnd << 0, 0, cmd->holdAltitude;
	myLine.lineVel << (myLine.lineEnd - myLine.lineStart) / cmd->duration;
	myLine.lineEpoch = cmd->time;
	myLine.duration = cmd->duration;

	yawCmd = atan2(myLine.lineVel(1), myLine.lineVel(0));
}
void Guidance::setInput(LiftoffData *cmd)
{

	if (guideMode == StateTypes::CONST_ACCEL)
	{
		myGuideCmd.reset = true;
		myGuideCmd.runAp = true;
		guideMode = StateTypes::PARABOLA;
		myParabolic.t0 = cmd->time;
		myParabolic.duration = cmd->duration;
		myParabolic.y0[0] = 0;
		myParabolic.y0[1] = 0;
		myParabolic.y0[2] = 0; // Start at NED Origin
		myParabolic.yHold[0] = 0;//vertical only
		myParabolic.yHold[1] = 0;//vertical only
		myParabolic.yHold[2] = cmd->hFinal;
		myParabolic.v0[0] = 0; //vertical only
		myParabolic.v0[1] = 0;//vertical only
		myParabolic.a[0] = 0;//vertical only
		myParabolic.a[1] = 0;//vertical only
		myParabolic.a[2] = ( cmd->hFinal ) / ( -.5*cmd->duration*cmd->duration );
		myParabolic.v0[2] = -myParabolic.a[2] * cmd->duration;
		
		/*guideMode = StateTypes::HOLDPOINT;
		stabilityCmd[0] = 0.0;
		stabilityCmd[1] = 0.0;
		stabilityCmd[2] = 5.0;*/
	}
}
void Guidance::setInput(LandingData *cmd)
{
	myGuideCmd.reset = true;
	guideMode = StateTypes::PARABOLA;
	myParabolic.t0 = cmd->time;
	myParabolic.duration = cmd->duration;
	myParabolic.y0[0] = myState.pos[0];//vertical only
	myParabolic.y0[1] = myState.pos[1];//vertical only
	myParabolic.y0[2] = myState.pos[2]; 
	myParabolic.yHold[0] = myState.pos[0];//vertical only
	myParabolic.yHold[1] = myState.pos[1];//vertical only
	myParabolic.yHold[2] = 0;//end at 0
	myParabolic.v0[0] = 0; //vertical only
	myParabolic.v0[1] = 0;//vertical only
	
	myParabolic.a[0] = 0;//vertical only
	myParabolic.a[1] = 0;//vertical only
	myParabolic.a[2] =  -myState.pos[2] / (-.5*cmd->duration*cmd->duration);
	myParabolic.v0[2] = -myParabolic.a[2]*cmd->duration; //start going down and end @ 0 vel
}

void Guidance::setInput(WaypointLocation *data)
{
	myGuideCmd.reset = true;
	guideMode = StateTypes::WAYPOINT;
	std::string fname(data->waypointFile);
	LoadTrajectory(fname);
	waypointEpoch_ = myState.time;
}


void Guidance::setInput(IdleCmd *data)
{
	myGuideCmd.reset = true;
	guideMode = StateTypes::CONST_ACCEL;
	idleCmd_.accel = data->accel;
}

void Guidance::calcCurvature()
{
	
	double V;
	double x1,x2,x3,y1,y2,y3,ma,mb,x,y;
	double R;
	double A;
	Eigen::Vector2d toCenter;
	V = sqrt(myState.vel.dot( myState.vel  ) );


	x3 = myState.pos[0];
	y3 = myState.pos[1];
	x2 = myLastState.pos[0];
	y2 = myLastState.pos[1];
	x1 = myLastState2.pos[0];
	y1 = myLastState2.pos[1];

	ma = (y2-y1)/(x2-x1);
	mb = (y3-y2)/(x3-x2);

	if( (mb-ma) != 0  && ma != 0)
	{
		x = ( ma*mb*(y1-y3) + mb*(x1+x2) - ma*(x2+x3))/(2 * ( mb-ma));
		y = ( (x1+x2)/2 - x )/ma + (y1+y2)/2;
	}
	{
		x = x3;
		y = y3;
	}
	toCenter << x-x3 ,  y-y3;
	
	R = sqrt( toCenter[0]*toCenter[0]  + toCenter[1]*toCenter[1] ) ;
	if( R > 0 ) 
	{
		A = V*V/R;
		acurve = A*( toCenter/R ) ;
		
	}
	else
	{
		acurve << 0 , 0;
		R= 0.0;
	}

}

bool Guidance::getOutput( GuidanceCmd *cmd)
{
	
	if( newCmdReady ) 
	{
		*cmd = myGuideCmd;
		
		newCmdReady = false;
		myGuideCmd.reset = false; 
		return true;
	}
	return false;
}

bool Guidance::getOutput(GuidanceReport *data)
{
	if (reportReady)
	{
		reportReady = false;
		data->mode = guideMode;
		return true;
	}
	return false;
}

void Guidance::getDebug( double *debugO)
{
	debugO[0] = debug[0];
	debugO[1] =debug[1];
	debugO[2] =debug[2];
}

void Guidance::populateFromWaypoint()
{
	// Look up position / vel cmd
	double waypointTime;
	waypointTime = myState.time  - waypointEpoch_;
	if (hTraj.timeInBounds(waypointTime))
	{

		VxCmd = vxTraj.CalcValue(waypointTime);
		VyCmd = vyTraj.CalcValue(waypointTime);
		xCmd = xTraj.CalcValue(waypointTime);
		yCmd = yTraj.CalcValue(waypointTime);
		hCmd = hTraj.CalcValue(waypointTime);
		yawCmd = atan2(VyCmd, VxCmd);
	}
	else
	{
		guideMode = StateTypes::HOLDPOINT;
		reportReady = true;
		VxCmd = 0;
		VyCmd = 0;
		stabilityCmd[0] = xTraj.endValue();
		stabilityCmd[1] = yTraj.endValue();
		stabilityCmd[2] = hTraj.endValue();
		populateHold();
	}
}

void Guidance::populateDirectLine()
{
	Eigen::Vector3d currLinePt;
	if( myLine.duration > (myState.time - myLine.lineEpoch) )
	{
		currLinePt = (myLine.lineVel)*( myState.time - myLine.lineEpoch) + myLine.lineStart;
		xCmd = currLinePt[0];
		yCmd = currLinePt[1];
		hCmd = currLinePt[2];
		VxCmd = myLine.lineVel[0];
		VyCmd = myLine.lineVel[1];
		yawCmd = atan2(VyCmd, VxCmd);
	}
	else
	{
		guideMode = StateTypes::HOLDPOINT;
		reportReady = true;
		stabilityCmd[0] = myLine.lineEnd[0];
		stabilityCmd[1] = myLine.lineEnd[1];
		stabilityCmd[2] = myLine.lineEnd[2];
		populateHold();
	}
}

void Guidance::populateHold()
{
	xCmd  = stabilityCmd[0];
	yCmd  = stabilityCmd[1];
	hCmd  = stabilityCmd[2];
	VxCmd = 0;
	VyCmd = 0;
//	yawCmd = 0;
}

void Guidance::populateConstAccel()
{
	double stateYaw;
	double q1, q2, q3, q4;
	q1 = myState.q[0];
	q2 = myState.q[1];
	q3 = myState.q[2];
	q4 = myState.q[3];
	stateYaw = atan2(-2 * (q1*q2 - q3*q4), (1 - 2 * q1*q1 - 2 * q3*q3));

	myGuideCmd.accel_cmd << 0, 0, idleCmd_.accel;
	myGuideCmd.v_cmd << 0, 0, 0;
	myGuideCmd.yawCmd = stateYaw;
	newCmdReady = true;
}

void Guidance::populateParabola()
{
	double tl;
	tl = myState.time - myParabolic.t0;
	xCmd = 0;
	yCmd = 0;
	if (tl < myParabolic.duration)
	{
		xCmd = .5*myParabolic.a[0] * tl*tl + myParabolic.v0[0] * tl + myParabolic.y0[0];
		yCmd = .5*myParabolic.a[1] * tl*tl + myParabolic.v0[1] * tl + myParabolic.y0[1];
		hCmd = .5*myParabolic.a[2] * tl*tl + myParabolic.v0[2] * tl + myParabolic.y0[2];

		VxCmd = myParabolic.v0[0] + myParabolic.a[0]* tl;
		VyCmd = myParabolic.v0[1] + myParabolic.a[1] * tl;
		yawCmd = atan2(VyCmd, VxCmd);
	}
	else
	{
		// Hold
		guideMode = StateTypes::HOLDPOINT;
		reportReady = true;
		stabilityCmd[0] = myParabolic.yHold[0];
		stabilityCmd[1] = myParabolic.yHold[1];
		stabilityCmd[2] = myParabolic.yHold[2];
		populateHold();
	}
}


void Guidance::populateCommandState()
{
	switch( guideMode ) 
	{
	case StateTypes::WAYPOINT:
		populateFromWaypoint();
		Iterate();
		break;
	case StateTypes::LINE:
		populateDirectLine( );
		Iterate();
		break;
	case StateTypes::PARABOLA:
		populateParabola( );
		Iterate();
		break;
	case StateTypes::HOLDPOINT:
		populateHold();
		Iterate();
		break;
	case StateTypes::CONST_ACCEL:
		populateConstAccel();
		break;
	default:
		std::cout << "Bad Guidance Mode...What the" << std::endl;
 		break;
	}
	
	
}

void Guidance::GroundSpinUp()
{
	double stateYaw;
	double q1,q2,q3,q4;
	q1 = myState.q[0];
	q2 = myState.q[1];
	q3 = myState.q[2];
	q4 = myState.q[3];
	stateYaw = atan2(-2 * (q1*q2 - q3*q4), (1 - 2 * q1*q1 - 2 * q3*q3));
	myGuideCmd.accel_cmd << 0, 0, 10.1; // spinup to half G
	myGuideCmd.v_cmd << 0, 0, 0;
	myGuideCmd.yawCmd = stateYaw;
	// LOok into x error

	newCmdReady = true;
}
void Guidance::Iterate()
{
	double DT;
	double XAccel;
	double YAccel;
	DT = myState.time - myLastState.time;
	if (DT <= 0)
	{
		DT = 0.01;
	}

	double hAccelCmd;

	double VXerr, VYerr, Vh;
	Eigen::Vector2d trackCmd, xyCmd;
	// Local Variables

	// Look up position / vel cmd
	/*VxCmd = vxTraj.CalcValue( myState.time );
	VyCmd = vyTraj.CalcValue( myState.time );
	xCmd  = xTraj.CalcValue( myState.time );
	yCmd  = yTraj.CalcValue( myState.time );
	hCmd  = hTraj.CalcValue( myState.time );*/

	Xerr = xCmd - myState.pos[0];
	Yerr = yCmd - myState.pos[1];
	Zerr = hCmd - myState.pos[2];
	VXerr = VxCmd - myState.vel[0];
	VYerr = VyCmd - myState.vel[1];
	Vh = myState.vel[2];
	debug[0] = Zerr;
	debug[1] = hCmd;
	debug[2] = myState.pos[2];




	// calc curvature accels
	calcCurvature();


	// Cross Track Control
	XAccel = posX.Iterate(Xerr, DT) + (VXerr * GainX.Kd);
	YAccel = posY.Iterate(Yerr, DT) + (VYerr * GainY.Kd);
	// Altitude Control
	hAccelCmd = posH.Iterate(Zerr, DT) + G0 - (GainH.Kd *Vh);
	//std::cout<<"Z: "<<Zerr<<" A:"<<hAccelCmd<<std::endl;

	hAccelCmd = Saturate(hAccelCmd, 3, 20);

	myGuideCmd.accel_cmd <<XAccel + acurve[0], YAccel + acurve[1], hAccelCmd;


	myGuideCmd.v_cmd << VxCmd, VyCmd, 0;
	myGuideCmd.yawCmd = yawCmd;
	// LOok into x error


	//std::cout<<"ACCEL: "<<myGuideCmd.accel_cmd <<std::endl;
	//std::cout<<"VCMD: "<<myGuideCmd.v_cmd<<std::endl;
	newCmdReady = true;
	
#ifdef DEBUG_DATA
	fprintf(debugFp,"%5.10f,", Xerr);
	fprintf(debugFp, "%5.10f,", Yerr);
	fprintf(debugFp, "%5.10f," ,Zerr);
	fprintf(debugFp, "%5.10f,", XAccel);
	fprintf(debugFp, "%5.10f,", YAccel);
	fprintf(debugFp, "%5.10f,", hAccelCmd);
	fprintf(debugFp, "%5.10f,", acurve[0]);
	fprintf(debugFp, "%5.10f,", acurve[1]);
	fprintf(debugFp, "\n");
#endif

}
