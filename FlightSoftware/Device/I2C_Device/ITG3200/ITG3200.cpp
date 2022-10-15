#include "ITG3200.h"
#include "Defines.h"


ITG3200::ITG3200()
{

}


ITG3200::~ITG3200()
{

}


void ITG3200::linkI2cBus( I2C_Device *dev )
{
	i2cBus = dev;
}

void ITG3200::setupDevice()
{

printf("1\n");

	cfgInterrupts(); // setup interrupts
printf("2\n");
	setSampleRate(100);// setup sample rate to 100Hz
printf("3\n");
	setpower();
printf("4\n");
}


void ITG3200::readITG3200(unsigned int reg, unsigned int totalReg, char *data)
{
	i2cBus->readI2c(ITG3200Map::deviceId, reg , totalReg , data  );
}

void ITG3200::writeITG3200(unsigned int reg, unsigned int totalReg, char *data)
{
	i2cBus->writeI2c( ITG3200Map::deviceId, reg , totalReg , data  );
}

void ITG3200::setSampleRate(int sampRate )
{
	char divider=0x00;
	char filterCfg = 0x00;
	int fastRate;
	int div;
	filterCfg |= ( ITG3200_Settings::FULLSCALE_RANGE << 3 );
	gyroScaleFactor = ITG3200_Settings::FULLSCALE_FACTOR * DEG2RAD;//in rad/s
	filterCfg |= ( ITG3200_Settings::ITG3200_Filter[ ITG3200_Settings::Filter_98KHZ ].setting )  ;

	fastRate = ITG3200_Settings::ITG3200_Filter[ ITG3200_Settings::Filter_98KHZ ].fastSampleRate;


	div = (fastRate/sampRate) - 1;
	divider |= (char)div;
	writeITG3200( ITG3200Map::DLPF_FS ,  1 ,&filterCfg);
	writeITG3200( ITG3200Map::SMPLRT_DIV , 1 , &divider);
//	printf("FilterCfg: %x\n",filterCfg);
//	printf("DivCfg: %x\n",divider);
}

void ITG3200::cfgInterrupts()
{

	char byte =0x00;

	//bit 7 left to 0 ---active low logict for int pin
	//bit 6 left to 0 for push pull drain
	//byte |= 1<<6;
	// bit 5 left to 0 for 50us pulse
	//byte |= 1<<5;
	//bit 4 left to 0 for status read=clear
	//byte |= 1<<4;
	//bit 3 = 0
	//bit 2 =  1  interrupt when pll ready
	byte |= ( 1 << 2 );
	//bit 0 = 1 enable data rdy interrupt
	byte |= 1;
	writeITG3200( ITG3200Map::INT_CFG , 1 , &byte);
}

void ITG3200::setpower()
{
 char byte = 0x00;
 //bit 7 = 0 no reset
 //bit 6 = 0 (not in sleep mode)
 //bit 5-3 = 0 do not sleep any of the gyro's
 //byte |=  0x01; // use x gyro as clk source???

 writeITG3200( ITG3200Map::PWR_MGM , 1,  &byte);
}

void ITG3200::getStatus()
{
	char intByte;

	readITG3200( ITG3200Map::INT_STATUS, 1, &intByte);
//	printf("ITGStat: %x\n",intByte);
	itgRdy = (intByte >> 2) == 1;
	dataRdy = (intByte & 0x01) ==1;



}


void ITG3200::readGyros(GryoVector *gout)
{
	short gyroX,gyroY,gyroZ;
	readITG3200( ITG3200Map::GYRO_XOUT_H   ,  6 , gyroData) ;
	

	gyroX = (gyroData[0] << 8) + gyroData[1];
	gyroY = (gyroData[2] << 8) + gyroData[3];
	gyroZ = (gyroData[4] << 8) + gyroData[5];

	gout->wx  = gyroX * gyroScaleFactor;
	gout->wy  = gyroY * gyroScaleFactor;
	gout->wz  = gyroZ * gyroScaleFactor;
}


bool ITG3200::dataWaiting()
{
	getStatus();
	if( dataRdy ) 
	{
		//printf("GoodGood\n");
		return true;
	}

	return false;
}
