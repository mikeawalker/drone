#ifndef ADXL345_H
#define ADXL345_H

#include "I2C_Device.h"
#include "Includes.h"
#include "ADXL345_MemMap.h"
#include "ADXL345_Settings.h"
class ADXL345
{
public:
	ADXL345();
	~ADXL345();
	
	void linkI2cBus( I2C_Device *dev );
	void readAccels(AccelVector *aout );
	bool accelsWaiting();
	void setupDevice();
private:
	float offsetX,offsetY,offsetZ;
	I2C_Device *i2cBus;
	void readADXL345(unsigned int reg , unsigned int totalReg , char *data);
	void writeADXL345( unsigned int reg , unsigned int totalReg , char *data);
	
	char accelData[6];
	// offset methods 
	void setupOffsets(float off_x , float off_y, float off_z);
	char calcOffsetByte( float offset );
	static const float OFFSET_SCALE;
	//
	void setupRate( unsigned char rate , bool lowPowerOn ) ;
	// range methods
	void setupDataFormat( unsigned char range , bool fullRes);
	float gScaleFactor;
	// fifo methods 
	void setupFifo(unsigned char fifoMode);
	int entriesWaiting;
	// power control
	void setupPowerControl(bool powerOn);

protected:

};
#endif