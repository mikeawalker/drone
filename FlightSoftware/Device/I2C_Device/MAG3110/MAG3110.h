#ifndef MAG3110_H
#define MAG3110_H

#include "I2C_Device.h"
#include "Mag3110_MemMap.h"
class MAG3110
{
public:
	MAG3110();
	~MAG3110();

	void linkI2cBus(I2C_Device *dev);
	void setupDevice();

	void readMags(MagVector *mout);
	bool magWaiting();
	void handleIntterupt(int sigNum );
private:
	I2C_Device *i2cBus;
	void readMAG3110(unsigned int reg, unsigned int totalReg, char *data);
	void writeMAG3110(unsigned int reg, unsigned int totalReg, char *data);
	void magBalance();
	void readStatus();
	bool rawEn;

	

	static const float RAW_MAG3110_TO_uT;
protected:
};

#endif