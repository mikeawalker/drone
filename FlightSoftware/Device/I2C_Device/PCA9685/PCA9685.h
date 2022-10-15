#ifndef PCA9685_H
#define PCA9685_H

#include "I2C_Device.h"
#include "PCA9685_MemMap.h"
#include "MyTime.h"

class PCA9685
{
public:
	enum MotorNumber
	{
		MOTOR1 = 0,
		MOTOR2,
		MOTOR3,
		MOTOR4,
		NUM_MOTORS
	};


	PCA9685();
	~PCA9685();
	void setupDevice();
	void linkI2CBus(I2C_Device * i2c);

	void commandMotor(BladeCmd *cmd);
	void escCalibration();
	void setPrf(double prf);

	void commandBlade(double duty, MotorNumber motor);



private:
	I2C_Device *i2cBus;
	void readPCA9685(unsigned int reg, unsigned int totalReg, char *data);
	void writePCA9685(unsigned int reg, unsigned int totalReg, char *data);
	void setupPwmDriver();

	double myPrf;

	static const unsigned int OFF_LOW_BYTE = 0;
	static const unsigned int OFF_HIGH_BYTE =1;
	static const unsigned int ON_LOW_BYTE = 2;
	static const unsigned int ON_HIGH_BYTE = 3;

	static const double MAX_MS_PULSE;
	static const double MIN_MS_PULSE;
	double MAX_CMD_RATE;
	unsigned int motorLocs[NUM_MOTORS][4];
	void writePwm();
	void commandBladePercent(double percent, MotorNumber motor);
	static const int clockRate = 25000000;

protected:

};

#endif