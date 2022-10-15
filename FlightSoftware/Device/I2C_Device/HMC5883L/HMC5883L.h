#ifndef HMC5883L_H
#define HMC5883L_H

#include "I2C_Device.h"
#include "HMC5883L_MemMap.h"
#include "HMC5883L_Settings.h"
#include "MyTime.h"
class HMC5883L
{
public:
	HMC5883L();
	~HMC5883L();

	void linkI2cBus( I2C_Device *dev );
	void readMags(MagVector *mout );
	bool magsWaiting();
	void setupDevice();
private:
	I2C_Device *i2cBus;
	void readHMC5883L(unsigned int reg , unsigned int totalReg , char *data);
	void writeHMC5883L( unsigned int reg , unsigned int totalReg , char *data);
	void magBalance();
	
	void magConfig(HMC5883L_Settings::MagSetup setup);
	void outputConfig( unsigned char mode );
	void getStatus();
	float magScaleFactor;
	bool rdyBit_;
	bool lockBit_;
	
	char magVec[6];
	double scaleX;
	double scaleY;
	double scaleZ;
	static const double GAUSS_TO_uTESLA;
protected:

};

#endif
