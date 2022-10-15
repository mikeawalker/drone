#include "Fake_Interface.h"
#include "Tools.h"


Fake_Interface::Fake_Interface(std::string bName ) : Block(bName,10,10) 
{
	firstMeasure = true;
	msCtr = 1;

}

Fake_Interface::~Fake_Interface()
{
	

}

void Fake_Interface::update()
{
	
	CheckSend();
	MyTime::mSleep(10);
	mtx.unlock();
	msCtr++;
	
}

void Fake_Interface::CheckSend()
{
	boost::posix_time::time_duration timeOut;
	currTime_  = boost::posix_time::microsec_clock::universal_time();
	if (firstMeasure)
	{
		firstTime_ = currTime_;
		firstMeasure = false;
	}
	timeOut = currTime_ - firstTime_;

	//Everytime
	imuMsg_.myData.a_b1 = 0.1;
	imuMsg_.myData.a_b2 = 0.2;
	imuMsg_.myData.a_b3 = 10.01;
	imuMsg_.myData.w_b1 = 0.01;
	imuMsg_.myData.w_b2 = 0.02;
	imuMsg_.myData.w_b3 = -0.033; // gyro z is inverted
	imuMsg_.myData.time = timeOut.total_milliseconds() * 0.001;
	sendMessage(&imuMsg_);
//	std::cout << "IMU " << std::endl;
	// 2 Hz
	if (msCtr % 10 == 0 )
	{
		double coLat;
		double Bu, Bn;
		double magB;
		Eigen::Vector3d mag1;
		mag1 << 0, 24.6, -40.4;
		
	//	mag1 << 24.6, 0.0, -40.4;
	//	mag2 << 0.0, 24.6, -40.4;

		magMsg_.myData.mag1_x = mag1(0);
		magMsg_.myData.mag1_y = mag1(1);
		magMsg_.myData.mag1_z = mag1(2);
		
		magMsg_.myData.time = timeOut.total_milliseconds() * 0.001;
		sendMessage(&magMsg_);
//		std::cout << "Mag Msg" << std::endl;
	}
	// 1 Hz
	if( (msCtr % 100) == 0 )
	{
		gpsMsg_.myData.X_ECEF = 0.0;
		gpsMsg_.myData.Y_ECEF = 0.0;
		gpsMsg_.myData.Z_ECEF = 5.0;
	
		gpsMsg_.myData.time = timeOut.total_milliseconds() * 0.001;
		//sendMessage( &gpsMsg_ );
		gpsAccelMsg_.myData.ax = 0.0;
		gpsAccelMsg_.myData.az = 0.0;
		gpsAccelMsg_.myData.ay = 0.0;
		//sendMessage(&gpsAccelMsg_);
//		printf("GPS PVT\n");		
	}
}
