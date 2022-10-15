#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include "Block.h"
#include "I2C_Device.h"
#include "Includes.h"
// in 
#include "BladeCmdMsg.h"
#include "MagInterrupt.h"
//out
#include "ImuMsg.h"
#include "MagMsg.h"

#include "ADXL345.h"
#include "HMC5883L.h"
#include "ITG3200.h"
#include "MAG3110.h"
#include "PCA9685.h"

#include "GPIO_Device.h"
//

#include "boost/date_time/posix_time/posix_time.hpp"

class I2C_Interface : public Block
{
public:
	I2C_Interface(std::string bName , bool cal );
	~I2C_Interface();
	void update();
	void CheckSend();

	void handleMag3110(int sigNum);
private:
	void read100HzDevices();
	void read10HzDevices();
	void readDevices();
	
	void fillMag();
	void loadMagCal(std::string fname, std::string fname2);
	void fillImu();
	I2C_Device myI2C;

	// in Msg
	BladeCmdMsg bladeCmdMsg_;
	MagInterrupt magWaitingMsg_;
	// out msg
	ImuMsg imuMsg_;
	MagMsg magMsg_;
	//Devices
	ADXL345 myAccel_;
	HMC5883L myMag_;
	ITG3200 myGyro_;
	MAG3110 myMag2_;
	PCA9685 myMotor_;
	GPIO_Device motorOE_;
	// Data
	AccelVector aout;
	MagVector mout;
	MagVector mout2;
	GryoVector gout;

	bool imuWaiting_;
	bool magWaiting_;

	Eigen::Matrix3d magCalDcm_;
	Eigen::Vector3d magCalOffsets;
	double magScaleXy_;


	Eigen::Matrix3d magCalDcm2_;
	Eigen::Vector3d magCalOffsets2;
	double magScaleXy2_;


	int interruptCount_;

	bool calMode_;
	bool firstMeasure;
	unsigned long msCtr;
	static const unsigned long MAG_MS = 33;
	static const unsigned long IMU_MS = 10;
	static const unsigned int OE_PIN = 22;
	boost::posix_time::ptime  currTime_;
	boost::posix_time::ptime  firstTime_;
protected:

};
#endif
