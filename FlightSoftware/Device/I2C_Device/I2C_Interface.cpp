
#include "I2C_Interface.h"


#include "XmlUtils.h"

I2C_Interface::I2C_Interface( std::string bName , bool cal) :  Block( bName , 10 , 10  ) ,
motorOE_("22")
{

	calMode_ = cal;
	msCtr = 0 ;
	interruptCount_ = 0;
	registerMessage(DroneMsgTypes::BladeCmdMsgId);
	registerMessage(DroneMsgTypes::MagInterruptId);

	imuWaiting_ = false;
	magWaiting_ =  false;
	firstMeasure = true;
	
	myI2C.openI2c("/dev/i2c-1");
	myAccel_.linkI2cBus(&myI2C);
	myMag_.linkI2cBus(&myI2C);
	myMag2_.linkI2cBus(&myI2C);
	myGyro_.linkI2cBus( &myI2C);
	myMotor_.linkI2CBus(&myI2C);


	myAccel_.setupDevice();
	myMag_.setupDevice();
	myMag2_.setupDevice();
	myGyro_.setupDevice();
	myMotor_.setupDevice();

	std::string mag1Cal;
	std::string mag2Cal;

	mag1Cal = XmlUtils::GetMag1FileName("Drone.xml");
	mag2Cal = XmlUtils::GetMag1FileName("Drone.xml");

	printf("AAA\n");
	loadMagCal(mag1Cal,mag2Cal);
	printf("BBB\n");

	myMag2_.readMags(&mout2);
	motorOE_.enable();
	motorOE_.setDirection("out");
	motorOE_.write("1");
}

I2C_Interface::~I2C_Interface()
{


}


void I2C_Interface::update()
{
//	printf("I2C\n");
	unsigned int header;
	boost::posix_time::ptime t1;
t1  = boost::posix_time::microsec_clock::universal_time();
	while( waitingMessages() )
	{
//		printf("22\n");
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::BladeCmdMsgId:
			rcvMessage( &bladeCmdMsg_ );
			myMotor_.commandMotor(&bladeCmdMsg_.myData);
			break;
		case DroneMsgTypes::MagInterruptId:
//			printf("Inttupt Msg\n");
			rcvMessage(&magWaitingMsg_);
			readDevices();
			break;
		default:
			printf("Bad Message Id [I2C]: %x \n", header);
			break;
		}
	}


	
	
	CheckSend();

//	printf("EXIT I2C\n");
}


void I2C_Interface::CheckSend()
{
	if( magWaiting_ )
	{
		fillMag();
//		printf("Mag Send\n");
		sendMessage(&magMsg_);
		magWaiting_ = false;
	}

	if( imuWaiting_ )
	{
		fillImu();
//		printf("Imu Send\n");
		sendMessage( &imuMsg_ );
		
		imuWaiting_ = false;

	}
}

void I2C_Interface::readDevices()
{
	interruptCount_++;
	read100HzDevices();
	if (interruptCount_ >= 10)
	{
		read10HzDevices();
		interruptCount_ = 0;
	}
}

void I2C_Interface::read100HzDevices()
{
	
	currTime_  = boost::posix_time::microsec_clock::universal_time();

//	printf("100Hz Rd\n");
//	std::cout<<currTime_<<std::endl;	
	while( myAccel_.accelsWaiting() )
	{
		//printf("BB\n");
		myAccel_.readAccels(&aout );
		imuWaiting_ = true;	
		if( firstMeasure )
		{
			firstTime_ = currTime_;
			firstMeasure = false;
		}
//		printf("Accels: %f %f %f\n " ,  aout.ax , aout.ay , aout.az); 
	}
	while( myGyro_.dataWaiting() )
	{
		//printf("CC\n");
		myGyro_.readGyros( &gout );
	//	printf("Gyro: %f %f %f\n " , gout.wx , gout.wy  , gout.wz ); 
	}


	
//std::cout<<"T: "<<boost::posix_time::microsec_clock::universal_time()-currTime_<<std::endl;


}

void I2C_Interface::read10HzDevices()
{
	currTime_  = boost::posix_time::microsec_clock::universal_time();
	if( firstMeasure )
		{
			firstTime_ = currTime_;
			firstMeasure = false;
		}
	
	myMag_.readMags( &mout );

	//	while (myMag2_.magWaiting())
	//{
		//		printf("Read Mags\n");
	//	myMag2_.readMags(&mout2);
//	}

//	printf("Mag: %f %f %f\n " ,mout.magx , mout.magy  , mout.magz ); 

	magWaiting_ = true;
}


void I2C_Interface::fillMag()
{
	double magMag;
	Eigen::Vector3d magMod;
	double magMag2;
	Eigen::Vector3d magMod2;
	boost::posix_time::time_duration timeOut;
	timeOut = currTime_ - firstTime_;
	
	

	magMod << mout.magx , mout.magy , mout.magz ; 
	magMod2 << mout2.magx, mout2.magy, -mout2.magz; // MAG3110 has z axis pointing up...so flip it yo
//	std::cout<<"MAG1: "<<magMod<<std::endl;
	magMod =  (magCalDcm_ * magMod) - magCalOffsets;
	magMod2 = (magCalDcm2_ * magMod2) - magCalOffsets2;
	//magMag = sqrt( magMod[0]*magMod[0] + magMod[1]*magMod[1] * magMod[2]*magMod[2] );
	//std::cout<<"M1: "<<magMod[0]<<" M2: "<<magMod[1]<<" M3: "<<magMod[2]<<std::endl;
	magMag = 1.0;// magMod.norm();
	magMag2 = 1.0;// magMod2.norm();
  //      std::cout<<"Mag: "<<magMod<<"  mag2: "<<magMod.norm()<<std::endl;
//	std::cout<<"Mag :"<<magMod(0)<<std::endl;
	if( calMode_ )
	{
		magMag = 1.0;
		magMag2 = 1.0;
	}

	magMsg_.myData.mag1_x = magMod(0) / magMag;
	magMsg_.myData.mag1_y = magMod(1) / magMag;
	magMsg_.myData.mag1_z = magMod(2) / magMag;

	magMsg_.myData.time = timeOut.total_milliseconds() * 0.001;
//	std::cout<<currTime_<<" "<<firstTime_<<std::endl;
}

void I2C_Interface::fillImu()
{
	boost::posix_time::time_duration timeOut;
	timeOut = currTime_ - firstTime_;
	// NOTE: Sensors all have different coordinate Frames
	// Define new frame in the "Sensor stick: Z is up  X points toward the pins....
	// This frame matches the magnetometer's predefined frame
	imuMsg_.myData.a_b1 = aout.ay;;
	imuMsg_.myData.a_b2 = aout.ax;
	imuMsg_.myData.a_b3 = aout.az;
	imuMsg_.myData.w_b1 = gout.wy;
	imuMsg_.myData.w_b2 = -gout.wx;
	imuMsg_.myData.w_b3 = -gout.wz; // gyro z is inverted
	imuMsg_.myData.time  = timeOut.total_milliseconds() * 0.001;
}


void I2C_Interface::loadMagCal(std::string fname , std::string fname2)
{
	double deltas[13]; // DCM and Offsets and xy scale
	FILE *fp;
	bool doit =false;

	if(!calMode_){
		fp = fopen(fname.c_str(), "rb");

		fread(deltas, sizeof(double), 14, fp);
		magCalDcm_ << deltas[0], deltas[1], deltas[2],
		      deltas[3], deltas[4], deltas[5],
		      deltas[6], deltas[7], deltas[8];
	magCalOffsets << deltas[9], deltas[10], deltas[11];
	magScaleXy_ = deltas[12];
	fclose(fp);
	}
	else
	{
	magCalDcm_ << 1,0,0
		     ,0,1,0,
                     0,0,1;
	magCalOffsets << 0,0,0;
	magScaleXy_ = 1.0;
	}
	std::cout << "Mag Dcm: " << magCalDcm_ <<std::endl;
	std::cout << "Mag Offset: " << magCalOffsets << std::endl;
	std::cout << "XY MAg Scale: "<<magScaleXy_<<std::endl;


	// second

	if (!calMode_)
	{
		fp = fopen(fname2.c_str(), "rb");

		fread(deltas, sizeof(double), 14, fp);
		magCalDcm2_ << deltas[0], deltas[1], deltas[2],
			deltas[3], deltas[4], deltas[5],
			deltas[6], deltas[7], deltas[8];
		magCalOffsets2 << deltas[9], deltas[10], deltas[11];
		magScaleXy2_ = deltas[12];
		fclose(fp);
	}
	else
	{
		magCalDcm2_ << 1, 0, 0
			, 0, 1, 0,
			0, 0, 1;
		magCalOffsets2 << 0, 0, 0;
		magScaleXy2_ = 1.0;
	}
	std::cout << "Mag Dcm: " << magCalDcm2_ << std::endl;
	std::cout << "Mag Offset: " << magCalOffsets2 << std::endl;
	std::cout << "XY MAg Scale: " << magScaleXy2_ << std::endl;


}

