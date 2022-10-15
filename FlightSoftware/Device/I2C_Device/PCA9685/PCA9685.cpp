#include "PCA9685.h"
#include "I2C_Device.h"
#include "Defines.h"


const double PCA9685::MAX_MS_PULSE = 3.0;
const double PCA9685::MIN_MS_PULSE = 1.0;
PCA9685::PCA9685()
{
	motorLocs[MOTOR1][OFF_HIGH_BYTE] = PCA9685Map::LED0_OFF_H;
	motorLocs[MOTOR1][OFF_LOW_BYTE] = PCA9685Map::LED0_OFF_L;
	motorLocs[MOTOR1][ON_HIGH_BYTE] = PCA9685Map::LED0_ON_H;
	motorLocs[MOTOR1][ON_LOW_BYTE] = PCA9685Map::LED0_ON_L;

	motorLocs[MOTOR2][OFF_HIGH_BYTE] = PCA9685Map::LED1_OFF_H;
	motorLocs[MOTOR2][OFF_LOW_BYTE] = PCA9685Map::LED1_OFF_L;
	motorLocs[MOTOR2][ON_HIGH_BYTE] = PCA9685Map::LED1_ON_H;
	motorLocs[MOTOR2][ON_LOW_BYTE] = PCA9685Map::LED1_ON_L;

	motorLocs[MOTOR3][OFF_HIGH_BYTE] = PCA9685Map::LED2_OFF_H;
	motorLocs[MOTOR3][OFF_LOW_BYTE] = PCA9685Map::LED2_OFF_L;
	motorLocs[MOTOR3][ON_HIGH_BYTE] = PCA9685Map::LED2_ON_H;
	motorLocs[MOTOR3][ON_LOW_BYTE] = PCA9685Map::LED2_ON_L;

	motorLocs[MOTOR4][OFF_HIGH_BYTE] = PCA9685Map::LED3_OFF_H;
	motorLocs[MOTOR4][OFF_LOW_BYTE] = PCA9685Map::LED3_OFF_L;
	motorLocs[MOTOR4][ON_HIGH_BYTE] = PCA9685Map::LED3_ON_H;
	motorLocs[MOTOR4][ON_LOW_BYTE] = PCA9685Map::LED3_ON_L;

}

PCA9685::~PCA9685()
{

}

void PCA9685::setupDevice()
{

	setupPwmDriver();
	setPrf(100);
	MAX_CMD_RATE = 1;
}

void PCA9685::linkI2CBus(I2C_Device *bus)
{
	i2cBus = bus;
}
void PCA9685::readPCA9685(unsigned int reg, unsigned int totalReg, char *data)
{
	i2cBus->readI2c(PCA9685Map::deviceId, reg, totalReg, data);
	
}


void  PCA9685::writePCA9685(unsigned int reg, unsigned int totalReg, char *data)
{
	unsigned int d = 0;
	memcpy(&d, data, 1);
	printf("Writing 0x%2x to 0x%2x \n", d, reg);
	i2cBus->writeI2c(PCA9685Map::deviceId, reg, totalReg, data);
}


void PCA9685::commandMotor(BladeCmd *cmd)
{
	double rate1, rate2, rate3, rate4;
	rate1 = (cmd->rate1 / MAX_CMD_RATE);
	rate2 = (cmd->rate2 / MAX_CMD_RATE);
	rate3 = (cmd->rate3 / MAX_CMD_RATE);
	rate4 = (cmd->rate4 / MAX_CMD_RATE);

#ifdef LINUX_DEVICE
        printf("ABC\n");


	commandBladePercent(rate1, MOTOR1);
	commandBladePercent(rate2, MOTOR2);
	commandBladePercent(rate3, MOTOR3);
	commandBladePercent(rate4, MOTOR4);
#endif
}
void PCA9685::commandBladePercent(double percent, MotorNumber motor)
{
	double duty;
	double ms;
	//
	ms = (percent*( MAX_MS_PULSE - MIN_MS_PULSE)) + MIN_MS_PULSE;
	duty = (ms * 0.001 )*myPrf;
	commandBlade(duty, motor);
}
void PCA9685::commandBlade(double duty, MotorNumber num)
{


	char offLow, offHigh, onLow, onHigh;
	


	// rate should be between 0 and 1;
	short offNum = duty * 4096; // scale


	// start pulse at 0 phase, no shift needed
	onLow = 0x00;
	onHigh = 0x00;
	offLow = (offNum & 0x00FF);
	offHigh = (offNum & 0x0F00)>>8 ;
	printf("%f %d 0x%x%x  0x%x%x\n", duty, offNum, onHigh, onLow, offHigh, offLow);
	//
	writePCA9685(motorLocs[num][OFF_LOW_BYTE], 1, &offLow);
	writePCA9685(motorLocs[num][OFF_HIGH_BYTE], 1, &offHigh);
	writePCA9685(motorLocs[num][ON_LOW_BYTE], 1, &onLow);
	writePCA9685(motorLocs[num][ON_HIGH_BYTE], 1, &onHigh);
}

void PCA9685::setupPwmDriver()
{

        char modeOut;
        readPCA9685(PCA9685Map::MODE1 , 1 , &modeOut);
       printf("Mode 1: %2x\n",modeOut);  
	char mode1 = 0x00;
	char restart, extclk, autoInc, sleep, sub1, sub2, sub3, allcall;
	restart = 0x00; // restart disabled
	extclk = 0x00; // use internal clock
	autoInc = 0x00;//autoIncrement disabled
	sleep = 0x00; // normal mode
	sub1 = 0x00;
	sub2 = 0x00;
	sub3 = 0x00;
	allcall = 0x01;
	mode1 |= (restart << 7);
	mode1 |= (extclk << 6);
	mode1 |= (autoInc << 5);
	mode1 |= (sleep << 4);
	mode1 |= (sub1 << 3);
	mode1 |= (sub2 << 2);
	mode1 |= (sub3 << 1);
	mode1 |= (allcall << 7);
	char mode2 = 0x00;
	char invert, och, outDvr, outne;
	invert = 0x00;
	och = 0x00;
	outDvr = 0x01;
	outne = 0x00;
	mode2 |= (invert << 4);
	mode2 |= (och << 3);
	mode2 |= (outDvr <<2);
	mode2 |= (outne << 0);
	writePCA9685(PCA9685Map::MODE1, 1, &mode1);
	writePCA9685(PCA9685Map::MODE2, 1, &mode2);
}
void PCA9685::setPrf(double prf)
{
	char oldmode;
	char newmode;
	std::cout << "Setting PRF to " << prf << std::endl;
	//set sleep to 1
	readPCA9685(PCA9685Map::MODE1, 1, &oldmode);
	newmode = (oldmode & 0x7F ) |  0x10; // set sleep bit
	writePCA9685(PCA9685Map::MODE1, 1, &newmode);
	// write the rate
	int prescale;
	prescale = int( clockRate  / (4096 * prf) ) -1 ;
	 char* prs = ( char*) &prescale;
	writePCA9685(PCA9685Map::PRE_SCALE, 1, prs);
	std::cout << "Prescale: " << prescale << std::endl;
	//set sleep to 0

	writePCA9685(PCA9685Map::MODE1, 1, &oldmode);
	
	MyTime::mSleep(5);
	oldmode |= 0x80;
	writePCA9685(PCA9685Map::MODE1, 1, &oldmode);

	myPrf = prf;
}

void PCA9685::escCalibration()
{
	char a;
	double maxDuty;
	double minDuty;
	std::cout << "Starting ESC Calibration..." << std::endl;

	std::cout << "Setting PRF to " << myPrf << std::endl;
	std::cout << "Setting Pulse width to " << MAX_MS_PULSE << " ms " << std::endl;
	commandBladePercent(1, PCA9685::MOTOR1);
	commandBladePercent(1, PCA9685::MOTOR2);
	commandBladePercent(1, PCA9685::MOTOR3);
	commandBladePercent(1, PCA9685::MOTOR4);
	std::cout << "PWM now at max output rate....Power on ESC, after initialization beeps 1 extra beep signifies storage of max pwm rate..." << std::endl;
	std::cout << "After the 'max stroage' beep type in anything" << std::endl;
	std::cout << "Setting Pulse width to " << MIN_MS_PULSE << " ms " << std::endl;
	std::cin >> a;
	commandBladePercent(0, PCA9685::MOTOR1);
	commandBladePercent(0, PCA9685::MOTOR2);
	commandBladePercent(0, PCA9685::MOTOR3);
	commandBladePercent(0, PCA9685::MOTOR4);
	std::cout << "PWM now at lowest output rate....2 beeps signifies lowest setting" << std::endl;
}
