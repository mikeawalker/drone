#include "PCA9685.h"
#include "I2C_Device.h"

#define LINUX_DEVICE 
void motorMenu(char, PCA9685*);
void spoolUpDown(PCA9685*);
void setDuty(PCA9685 *motor);
int main(void)
{

	I2C_Device myI2C;
	PCA9685 myMotor_;
	myI2C.openI2c("/dev/i2c-1");
	myMotor_.linkI2CBus(&myI2C);
	myMotor_.setupDevice();
	int choice = 44;
	//myMotor_.escCalibration();
	while (choice != 5)
	{
		std::cout << "Enter operation for Motor: \n 1) Calibrate \n 2) Spool Up Spool Down 3) enter duty 4) set prf\n 5) Quit" << std::endl;
		std::cin >> choice;
		motorMenu(choice, &myMotor_);
	}
	return 0;
}


void motorMenu(char choice , PCA9685 *motor)
{
	double prf;
	switch (choice)
	{
	case 1:
		motor->escCalibration();
		break;
	case 2:
		spoolUpDown(motor);
		break;
	case 3:
		setDuty(motor);
		break;
	case 4:
		std::cout << "Enter PRF" << std::endl;
		std::cin >> prf;
		motor->setPrf(prf);
		break;
	case 5:

		break;
	default:
		break;
	}
}


void spoolUpDown(PCA9685 *motor)
{
	BladeCmd cmd;
	cmd.rate1 = .15;
	cmd.rate2 = .15;
	cmd.rate3 = .15;
	cmd.rate4 = .15;
	std::cout << "Spooling up Motor to 0.5" << std::endl;
	motor->commandMotor(&cmd);
	std::cout << "Hit any key to spool down " << std::endl;

	cmd.rate1 = 0;
	cmd.rate2 = 0;
	cmd.rate3 = 0;
	cmd.rate4 = 0;
	motor->commandMotor(&cmd);

}

void setDuty(PCA9685 *motor)
{
	double duty;
	std::cout << "Enter Duty Cycle " << std::endl;
	std::cin >> duty; 

	std::cout << "Spooling up Motor to: " << duty <<std::endl;
	

	motor->commandBlade(duty, PCA9685::MOTOR1);
	motor->commandBlade(duty, PCA9685::MOTOR2);
	motor->commandBlade(duty, PCA9685::MOTOR3);
	motor->commandBlade(duty, PCA9685::MOTOR4);
}