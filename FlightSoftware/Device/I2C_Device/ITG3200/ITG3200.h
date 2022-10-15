#ifndef ITG3200_H
#define ITG3200_H

#include "I2C_Device.h"
#include "ITG3200_MemMap.h"
#include "ITG3200_Settings.h"
class ITG3200
{
public:
	ITG3200();
	~ITG3200();
	void linkI2cBus( I2C_Device *dev );
	void readGyros(GryoVector *gout );
	bool dataWaiting();
	void setupDevice();
private:
	char gyroData[6];
	I2C_Device *i2cBus;
	float gyroScaleFactor;
	void readITG3200(unsigned int reg , unsigned int totalReg , char *data);
	void writeITG3200(unsigned int reg , unsigned int totalReg , char *data);


	void setSampleRate(int sampRate );
	void setpower( );
	void cfgInterrupts();
	void getStatus();

	bool itgRdy;
	bool dataRdy;
protected:
};
#endif

