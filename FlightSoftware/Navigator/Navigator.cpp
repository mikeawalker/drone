#include "Navigator.h"



Navigator::Navigator() 
{
	propegateSteps = 10;
	lastTime_ =-1/100.0;
	g0_ << 0 , 0 , -9.80665;
	
	C_mag = Eigen::MatrixXd::Zero(6,15);
	C_gps = Eigen::MatrixXd::Zero(3,15);
	
	P_ = Eigen::MatrixXd::Zero(15,15);
	dx_ = Eigen::VectorXd::Zero(15);
	dxUp_ = Eigen::VectorXd::Zero(15);
	Q_ = Eigen::MatrixXd::Zero(6,6);
	R_gps = Eigen::MatrixXd::Zero(3,3);
	R_mag = Eigen::MatrixXd::Zero(6,6);
	A_ = Eigen::MatrixXd::Zero(15,15);
	G_ = Eigen::MatrixXd::Zero(15,6);
	yGps_ = Eigen::VectorXd::Zero(3);
	yGpsMeasure_ = Eigen::MatrixXd::Zero(3,1);
	yMag_ = Eigen::VectorXd::Zero(6, 1);
	yMagMeasure_ = Eigen::VectorXd::Zero(6, 1);
	aBias_ = Eigen::Vector3d::Zero(3);
	wBias_ = Eigen::Vector3d::Zero(3);
	wMeasure_= Eigen::Vector3d::Zero(3);
	wTrue_= Eigen::Vector3d::Zero(3);
	aMeasure_= Eigen::Vector3d::Zero(3);
	aTrue_= Eigen::Vector3d::Zero(3);
	

	earthSurfaceENU_ << 0, 0, REarth;
	accelEstEnu_ << 0, 0, 0;
	//std::cout<<"\nP: " <<P_;
	newStateReady_ = false;
	firstOrientRcv_ = false;
	firstPosRcv_ = false;
	firstAccelRcv_ = false;
	firstBiasRcv_ = false;
	navInit_ = false;
	//debugOn = true;
	debugPrint = false;
	dcmMag2_ << 0,-1,0,
		    1,0,0,
                    0,0,1; // 90 deg rotation
	//firstPosRcv_ = true;
	//firstAccelRcv_ = true;
	//firstOrientRcv_ = true;
	if( debugOn )
	{
		covFile = fopen( "kalmanDebug.dat" , "w" ) ;
		stateFile = fopen( "stateFile.dat" , "w");
		debugFile = fopen("debug.dat", "w");
		fprintf(stateFile, "xKf, yKf, zKf, vxKf,vyKf, vzKf, q0Kf, q1Kf, q2Kf, q3Kf, ab1Kf, ab2Kf, ab3Kf, wb1Kf, wb2Kf,wb3Kf \n");
		for (int k = 0; k < 15; k++)
		{
			fprintf(covFile, "P%d%d_Kf,", k, k);
		}
		fprintf(covFile, "\n");

		fprintf(debugFile, "xpKf, ypKf , zpKf , xmKf, ymKf , zmKf \n");
	}	

}

void Navigator::Initialize()
{

	
	
	
}

Navigator::~Navigator()
{
	if(debugOn)
	{
		fclose(covFile);
		fclose(stateFile);
		fclose(debugFile);
	}
}


void Navigator::setDcm( ) 
{
	
	double q1,q2,q3,q4;
	q1 = qHat_(0);
	q2 = qHat_(1);
	q3 = qHat_(2);
	q4 = qHat_(3);
	dcmC2b_ <<  1-2*q2*q2-2*q3*q3 , 2*(q1*q2 + q3*q4) , 2*(q3*q1 - q2*q4) ,
               2*(q1*q2 - q3*q4) , 1 - 2*q1*q1 - 2*q3*q3 , 2*(q3*q2 + q1*q4), 
               2*(q1*q3 + q2*q4) , 2*(q3*q2 - q1*q4) , 1 - 2*q2*q2 - 2*q1*q1;
   
}


void Navigator::setInput( DroneNavInfo *data )
{

	Q_.block<3,3>(0,0) = data->accelVar.asDiagonal();
	Q_.block<3,3>(3,3) = data->gyroVar.asDiagonal();

	R_gps = data->gpsPosVar.asDiagonal();
	std::cout << R_gps << std::endl;
	R_mag = data->magVar.asDiagonal();
}

void Navigator::Propegate()
{
	Eigen::Matrix3d DCM;
	double dtProp = (currTime_ - lastTime_)/( (double) propegateSteps );
	dtProp = (0.01 / propegateSteps);
	Eigen::Vector3d vk;
	Eigen::Vector3d ak;
	Eigen::Vector3d g0;
	Eigen::Vector3d rk;
	Eigen::Vector4d qdot;
	Eigen::Vector4d qk;
	Eigen::Matrix4d OM;
	
	double q1,q2,q3,q4;
	double w1 , w2 , w3;
//	std::cout << "DT Prop: " << dtProp << std::endl;
	if( (currTime_ - lastTime_) > -1)//to save processor wait till next time
	{
		w1=  wTrue_(0) ; w2 = wTrue_(1) ; w3 = wTrue_(2);
		OM << 0, w3, -w2, w1
			  ,-w3, 0, w1, w2
			  ,w2, -w1, 0, w3
			  , -w1, -w2, -w3,0;
		rk <<rHat_;
		vk << vHat_;
		qk << qHat_;
		
		/*std::cout<<rk<<" " << vk << " " << qk ;*/
		for( int k = 0 ; k<propegateSteps ; k++)
		{
			q1 = qk(0); q2 = qk(1); q3 = qk(2); q4 = qk(3); 
			// note this is dcm b -> c
			DCM  << (1- (2*q2*q2) - (2*q3*q3)) , 2*(q1*q2 - q3*q4)  , 2*(q3*q1 + q2*q4),
					2*(q1*q2 + q3*q4) , 1-(2*q1*q1)-(2*q3*q3) , 2*( q3*q2 - q1*q4) ,
					2*(q1*q3 - q2*q4) , 2*(q3*q2 + q1*q4) , 1-(2*q2*q2) - (2*q1*q1) ;
			ak = DCM*aTrue_ + g0_; 
			vk = ak*dtProp + vk; 
			rk = rk + vk*dtProp + .5*dtProp*dtProp*ak;  
			qdot = .5*OM*qk;
			qk = qdot*dtProp + qk ;
			qk = qk/sqrt(qk.dot(qk));


		}

		rHat_ = rk;
		vHat_ = vk;
		qHat_ = qk;
		
		setDcm();

	}
	else
	{
		// Do nothing!
	}
	/*std::cout<<"r+: "<<rk<<std::endl;
	std::cout<<"v+: "<<vk<<std::endl;
	std::cout<<"a+: "<<ak<<std::endl;
	std::cout<<"q+: "<<qk<<std::endl;*/
}


void Navigator::CorrectImuToFrame()
{
	// IMU Moment ARM
}


void Navigator::setImuPosition( double r_b1 , double r_b2 , double r_b3  )
{
	imuLoc_ << r_b1,r_b2,r_b3;
}

void Navigator::setGpsPosition(double r_b1 , double r_b2 , double r_b3)
{
	gpsLoc_ << r_b1,r_b2,r_b3;
}


void Navigator::setInput( CovData *data ) 
{
	P_ = data->Covs.asDiagonal();
	//std::cout<<"\n P "<<P_;
}

void Navigator::setInput( StateVector *data )
{
	rHat_ = data->r;
	vHat_ = data->v;
	qHat_ = data->q;
    aBias_ = data->aBias;
	wBias_ = data->wBias;
/*	navInit_ = true;
	firstOrientRcv_ = true;
	firstPosRcv_ = true;
	firstBiasRcv_ = true;*/
	setDcm();
}


void Navigator::setInput(ImuMeasurement *imuIn)
{
	yGps_ = Eigen::VectorXd::Zero(3);

	aMeasure_ << imuIn->a_b1, imuIn->a_b2, imuIn->a_b3;
	wMeasure_ << imuIn->w_b1, imuIn->w_b2, imuIn->w_b3;
	wTrue_ = wMeasure_ - wBias_;
	aTrue_ = aMeasure_ - aBias_;
	currTime_ = imuIn->time;
	if (navInit_)
	{
	
	
		// KF Calls Here

		KalmanTimeProp(); // Linearize EOM/Propegate P
		Propegate();

		newStateReady_ = true;

		// time update
		lastTime_ = currTime_;
	}
	else
	{
		// do nothing until we init
		SetupFirstBias(imuIn);
	}
	
}
void Navigator::setInput( GpsMeasurement *gpsIn )
{
	// 
	Eigen::Vector3d Recef;
	Recef << gpsIn->X_ECEF, gpsIn->Y_ECEF, gpsIn->Z_ECEF;
	currTime_ = gpsIn->time;
	
	// KF Calls here
	if (navInit_)
	{
		yGpsMeasure_ = (dcmEcef2Local_*Recef) - earthSurfaceENU_;// , gpsIn->Vx_ECEF, gpsIn->Vy_ECEF, gpsIn->Vz_ECEF;
		
		if (debugPrint)
		{
			std::cout << "Nav: " << yGpsMeasure_ << std::endl;
		}
//		Propegate();
	
		PredictGps();
		KalmanGpsUpdate();
		ApplyTranslationCorrections();
		ApplyAttitudeCorrections();
		// time update
		lastTime_ = currTime_;
	}
	else
	{
		SetupFirstPos(gpsIn);
	}
}

void Navigator::setInput(AccelVector *accelVec)
{
	//Rotate to ENU
	Eigen::Vector3d accelEcef;
	accelEcef << accelVec->ax, accelVec->ay, accelVec->az;
	accelEstEnu_ <<dcmEcef2Local_*accelEcef;
}

void Navigator::setInput(MagMeasurement *magIn)
{
	

	

	//	std::cout<<"M2: "<<yMagMeasure_<<std::endl;
	currTime_ = magIn->time;
	if (navInit_)
	{
		KalmanTimeProp();
		EstimateGravityVector();
		yMagMeasure_ << magIn->mag1_x, magIn->mag1_y, magIn->mag1_z, 
						gravEstimate_(0), gravEstimate_(1), gravEstimate_(2) ;
	//	std::cout << "MagM: " << yMagMeasure_ << std::endl;
	//	Propegate();
		PredictMag();
		KalmanMagUpdate();
		ApplyAttitudeCorrections();
		ApplyTranslationCorrections();
		//time update
		lastTime_ = currTime_;
	}
	else
	{
		SetupFirstOrient(magIn);
	}
}

void Navigator::SetupFirstBias(ImuMeasurement *imu)
{
	if (!firstBiasRcv_)
	{

		aBias_ << imu->a_b1, imu->a_b2, (imu->a_b3 - G0);
		wBias_ << imu->w_b1, imu->w_b2, imu->w_b3;
		aTrue_ << aMeasure_ - aBias_;
		wTrue_ << wMeasure_ - wBias_;
		firstBiasRcv_ = true;
	}
	std::cout << "First Bias " << std::endl;
	CheckInit();
}
void Navigator::SetupFirstOrient(MagMeasurement *mag)
{
	double yawAngle;
	double rollAngle;
	double pitchAngle;
	double q4, q3;
	// Assume we are on a flat surface
	rollAngle = 0.0;
	pitchAngle = 0.0;
	yawAngle = atan2(mag->mag1_x, mag->mag1_y);
	q3 = sin(yawAngle / 2);
	q4 = cos(yawAngle / 2);
	qHat_ << 0, 0, q3, q4;
	
	firstOrientRcv_ = true;
	std::cout << "Nav Orient Rcv " << std::endl;
	CheckInit();
}

void Navigator::CheckInit()
{
	navInit_ = (firstOrientRcv_ && firstPosRcv_ &&  firstBiasRcv_);
	if (navInit_)
	{
		lastTime_ = currTime_;
	}
}
void Navigator::SetupFirstPos(GpsMeasurement *gps)
{
	firstPosRcv_ = true;
	std::cout << "Nav Pos Rcv " << std::endl;
	double lat0;
	double long0;
	Eigen::Matrix3d longRot;
	Eigen::Matrix3d latRot;
	Eigen::Matrix3d uenToenu;

	uenToenu << 0, 1, 0,
		0, 0, 1,
		1, 0, 0;
	long0 = atan2(gps->Y_ECEF, gps->X_ECEF);
	lat0 = atan(gps->Z_ECEF / sqrt(gps->X_ECEF*gps->X_ECEF + gps->Y_ECEF*gps->Y_ECEF));

	longRot << cos(long0), sin(long0), 0,
			   -sin(long0), cos(long0), 0,
			   0, 0, 1;
	latRot << cos(lat0), 0, sin(lat0),
			   0, 1, 0,
			  -sin(lat0),0,cos(lat0);
	dcmEcef2Local_ = uenToenu*latRot*longRot;

	

	rHat_ << gps->X_ECEF, gps->Y_ECEF, gps->Z_ECEF;
	earthSurfaceENU_ <<0,0, rHat_.norm() ;
	rHat_ = dcmEcef2Local_*rHat_ - earthSurfaceENU_;
	CheckInit();
	

}


void Navigator::EstimateGravityVector()
{
	gravEstimate_ = dcmC2b_*accelEstEnu_ - aTrue_; 
	//	gravEstimate_ = gravEstimate_ / gravEstimate_.norm();

}

void Navigator::PredictGps()
{

	Eigen::Vector3d rPredict;
	Eigen::Vector3d vPredict;
	rPredict = rHat_ + dcmC2b_.transpose()*gpsLoc_;
	vPredict = vHat_;// +dcmC2b_.transpose()*wTrue_.cross(gpsLoc_);
	//std::cout<< yGps_.block<3,1>(0,0) << " " << rPredict;
	yGps_ = rPredict;
	C_gps.block<3,3>(0,0) = Eigen::MatrixXd::Identity(3,3);
	
}

void Navigator::PredictMag()
{
	
	Eigen::Vector3d mField;
	Eigen::Vector3d mHat;
	Eigen::Matrix3d magSkew;
	Eigen::Matrix3d accelSkew;
	Eigen::Vector3d magEnu, gravEnu;
	Eigen::Vector3d magB, gravB;
	double coLat;
	double Bu;
	double Bn;
	double Be;
	double m1, m2, m3;
	double a1, a2, a3;
	coLat = 90- 32.2;
	Bu = -38.7; -40.4;
	Bn = 30.6;
//	//-0.854116895122904          0.52008107970355
	//Bu = -0.854116895122904;
	//Bn = 0.52008107970355;
	magEnu << 0, Bn, Bu;
	//magEnu = magEnu / magEnu.norm();
	gravEnu << 0, 0, -G0;
	//gravEnu = gravEnu / gravEnu.norm();
    //std::cout<<"MHAT: "<<mHat<<std::endl;
	magB = dcmC2b_* magEnu;
	gravB = dcmC2b_* gravEnu;
	// Populate C mag
//	std::cout<<"MAGS: "<<yMag_<<std::endl;
	// two mags , second has  90 deg roation
	yMag_ << magB(0), magB(1), magB(2), gravB(0), gravB(1), gravB(2);

	m1 = magEnu(0);
	m2 = magEnu(1);
	m3 = magEnu(2);
	magSkew << 0, m3, -m2,
		-m3, 0, m1,
		m2, -m1, 0;
			
	C_mag.block<3,3>(0,ANGLE) = dcmC2b_*(magSkew.transpose());
	a1 = gravEnu(0);
	a2 = gravEnu(1);
	a3 = gravEnu(2);
	accelSkew << 0, a3, -a2,
		-a3, 0, a1,
		a2, -a1, 0;
	C_mag.block<3, 3>(3, ANGLE) = dcmC2b_*(accelSkew.transpose());

}

void Navigator::LinearizeEom()
{
	Eigen::MatrixXd abSkew;
	Eigen::Vector3d accelC;
	Eigen::Matrix3d Wx;
	double w1, w2, w3;
	G_ = Eigen::MatrixXd::Zero(15, 6);
	A_ = Eigen::MatrixXd::Zero(15, 15);
	abSkew = Eigen::MatrixXd::Zero(3,3);


	accelC = (dcmC2b_.transpose() * aMeasure_);
	abSkew << 0 , -accelC(2)  , accelC(1) ,
			  accelC(2) , 0 , -accelC(0)  ,
			  -accelC(1) , accelC(0) , 0 ;



	//std::cout << "W: " << wTrue_ << std::endl;
	
	// Translational
	A_.block<3, 3>(POSITION, VELOCITY) =  Eigen::MatrixXd::Identity(3, 3);
	A_.block<3,3>(VELOCITY,ANGLE) = abSkew;
	A_.block<3,3>(VELOCITY,ACCEL_BIAS) =  -dcmC2b_.transpose(); 
	G_.block<3, 3>(VELOCITY, ACCEL_NOISE) = dcmC2b_.transpose();
	// Rotational
	w1 = wTrue_(0);
	w2 = wTrue_(1);
	w3 = wTrue_(2);
	Wx << 0 ,w3 ,-w2, -w3, 0, w1, w2 ,-w1, 0;
	A_.block<3, 3>(ANGLE, ANGLE) =-Wx;
	A_.block<3, 3>(ANGLE, GYRO_BIAS) = -dcmC2b_.transpose();
	//std::cout<< "A_ " << A_;  
	G_.block<3, 3>(ANGLE, GYRO_NOISE) = Eigen::Matrix3d::Identity();

//	std::cout << A_ << std::endl;
	// rotational


}

void Navigator::KalmanMagUpdate()
{
	
	Eigen::MatrixXd K;
	dx_ = Eigen::VectorXd::Zero(15);
	
	//
	Eigen::MatrixXd S;
	Eigen::VectorXd y_tilde;

	y_tilde = yMagMeasure_ - yMag_;

//	std::cout<<"Ymag: "<< yMagMeasure_<<" predict: "<<yMag_  << std::endl;
	S = Eigen::MatrixXd::Zero(6,6);
	S = C_mag*P_*C_mag.transpose() + R_mag;
	K = P_ * C_mag.transpose() * S.inverse();
	P_ = P_ - K * C_mag * P_;
	dx_ = K * y_tilde;
	
	//std::cout<< "\nC " << C_mag;
	//std::cout<<"\n K " <<K;
//	std::cout<<"\n dx " <<dx_;

	}
void Navigator::KalmanGpsUpdate()
{
	

	Eigen::MatrixXd K;
	dx_ = Eigen::VectorXd::Zero(15);
	
	
	Eigen::MatrixXd S;
	Eigen::VectorXd y_tilde;
	y_tilde = Eigen::VectorXd::Zero(3);
		//std::cout<<"\n P : "<<P_;
	y_tilde = yGpsMeasure_ - yGps_;
	//std::cout << "GPS: " << yGpsMeasure_ << std::endl;;
	S = Eigen::MatrixXd::Zero(3,3);
	S = C_gps*P_*C_gps.transpose() + R_gps;
	K = P_ * C_gps.transpose() * S.inverse();
	P_ = P_ - K * C_gps * P_;
	dx_ = K * y_tilde;


	//std::cout<< "\nP " << P_;
//	std::cout<<"\n K " <<K;
	//std::cout<<"\n dx " <<dx_<<std::endl;
}


void Navigator::KalmanTimeProp()
{
	LinearizeEom();
	Eigen::MatrixXd STM(15,15);
	//std::cout<<"\n D : "<<dcmC2b_;
	double dt = 0.01;
	STM = Eigen::MatrixXd::Identity(15, 15) + A_*(dt);
	//std::cout<<"\n \n : "<<A_;
	P_ = STM*P_*STM.transpose() + G_*Q_*G_.transpose();
	
	//std::cout << Q_ << std::endl;
//	std::cout<<"\n D : "<<dcmC2b_;
	//std::cout<<"\n STM : "<<STM;	
	//std::cout<<"\n G_: "<<G_;
   //std::cout<<"\n P 2: "<<P_;
	//std::cout << "Time Prop " << currTime_ << " " << lastTime_ << " " << currTime_ - lastTime_ << std::endl;
}


void Navigator::ApplyTranslationCorrections()
{
	rHat_ = rHat_ + dx_.block<3, 1>(POSITION, 0);
	vHat_ = vHat_ + dx_.block<3, 1>(VELOCITY, 0);

	aBias_ = aBias_ + dx_.block<3, 1>(ACCEL_BIAS, 0);

}

void Navigator::ApplyAttitudeCorrections()
{
	double p1, p2, p3, p4;
	double scale, mag1;
	Eigen::Vector3d qup1;
	qup1 << dx_.block<3, 1>(ANGLE, 0);
	mag1 = std::sqrt(qup1.dot(qup1))*0.5;
	if (mag1 <= 1)
	{
		scale = 1 / std::sqrt(1 - mag1);
	}
	else
	{
		scale = 1 / std::sqrt(1 + mag1);
	}
	Eigen::MatrixXd P(4, 4);
	Eigen::Vector4d qup;
	p1 = scale*.5*dx_(6);
	p2 = scale*.5*dx_(7);
	p3 = scale*.5*dx_(8);
	p4 = scale * 1;


	P << p4, -p3, p2, p1,
		p3, p4, -p1, p2,
		-p2, p1, p4, p3,
		-p1, -p2, -p3, p4;


	qup = P*qHat_;
	qHat_ = qup;// / qup.norm();//normalize
	wBias_ = wBias_ + dx_.block<3,1>(GYRO_BIAS,0);

	setDcm();
}


void Navigator::getOutput( StateVector *data )
{
	data->r = rHat_;
	data->v = vHat_;
	data->q = qHat_;
	data->aBias = aBias_;
	data->wBias = wBias_;
}


bool Navigator::getOutput( FullState *data )
{
	if( newStateReady_ )
	{
		newStateReady_ = false;
		data->pos = rHat_;
		data->vel = vHat_;
		data->q = qHat_;
		data->omega = wTrue_;
		data->accel = aTrue_;
		data->time = currTime_;
     //           std::cout<<"State Time:"<<currTime_<<std::endl;
		return true;
	}

	return false;
}

void Navigator::outputCovData()
{
	if( debugOn ) 
	{
		for (int k = 0; k < 15; k++)
		{

			fprintf(covFile, "%10.20f,", P_(k, k));
		}

		fprintf(covFile, "\n");
	}
}

void Navigator::outputDebugData()
{

	fprintf(debugFile, "%4.20f ,%4.20f, %4.20f ,%4.20f, %4.20f, %4.20f\n", yGps_(0), yGps_(1), yGps_(2), yGpsMeasure_(0), yGpsMeasure_(1), yGpsMeasure_(2));
}

void Navigator::outputStateData()
{
	if( debugOn ) 
	{
	//fprintf(stateFile , "%f,", currTime_  );
	fprintf(stateFile, "%7.20f,", rHat_(0));
	fprintf(stateFile, "%7.20f,", rHat_(1));
	fprintf(stateFile, "%7.20f,", rHat_(2));
	fprintf(stateFile, "%4.20f,", vHat_(0));
	fprintf(stateFile, "%4.20f,", vHat_(1));
	fprintf(stateFile, "%4.20f,", vHat_(2));
	fprintf(stateFile, "%4.20f,", qHat_(0));
	fprintf(stateFile, "%4.20f,", qHat_(1));
	fprintf(stateFile, "%4.20f,", qHat_(2));
	fprintf(stateFile, "%4.20f,", qHat_(3));
	fprintf(stateFile, "%4.20f,", aBias_(0));
	fprintf(stateFile, "%4.20f,", aBias_(1));
	fprintf(stateFile, "%4.20f,", aBias_(2));
	fprintf(stateFile, "%4.20f,", wBias_(0));
	fprintf(stateFile, "%4.20f,", wBias_(1));
	fprintf(stateFile, "%4.20f,", wBias_(2));
	fprintf(stateFile, "\n");
	}
	
}
