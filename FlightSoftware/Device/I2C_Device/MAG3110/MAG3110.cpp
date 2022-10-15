#include "MAG3110.h"

//const float MAG3110::RAW_MAG3110_TO_uT = 2000.0/(65536.0) ;//+- 1000 uT fullscale (check output rang lsb range)
const float MAG3110::RAW_MAG3110_TO_uT = 0.1;//+- 1000 uT fullscale (check output rang lsb range)


MAG3110::MAG3110()
{

}

MAG3110::~MAG3110()
{

}

void MAG3110::setupDevice()
{
//	printf("A\n");
	char whoamI;
	readMAG3110(MAG3110Map::WHO_AM_I, 1, &whoamI);
	if (whoamI != 0xC4)
	{
		std::cout << " MAG3110 WhoamI does not match 0xC4: " << whoamI <<"."<<  std::endl;
	}
	// Config 1:
	char fastRead = 0x00;
	char trigger = 0x00;
	char active = 0x01;
	char oversampRatio = 0x00; //oversample of 8 (2^3)
	char dataRate = 0x00;

	char cfg1;
	cfg1 = 0x00;
	cfg1 |= (dataRate <<5 ) & 0xE0;
	cfg1 |= (oversampRatio << 3) &0x18;
	cfg1 |= (fastRead << 2) & 0x4;
	cfg1 |= (trigger << 1) & 0x02;
	cfg1 |= (active << 0) & 0x01;

	//Config 2
	char raw;
	char automrst_en;
	char magrst;
	char cfg2;

	magrst = 0x0;
	automrst_en = 0x1;
	raw = 0x01;
	rawEn = true;
	cfg2 = 0x00;
	cfg2 |= (automrst_en << 7) & 0x80;
	cfg2 |= (raw << 5) & 0x20;
	cfg2 |= (magrst << 4) & 0x10;

	writeMAG3110(MAG3110Map::CTRL_REG1, 1, &cfg1);
	writeMAG3110(MAG3110Map::CTRL_REG2, 1, &cfg2);


	//Write Offsets to 0
	char z = 0x00;
	writeMAG3110(MAG3110Map::OFF_X_LSB, 1, &z);
	writeMAG3110(MAG3110Map::OFF_X_MSB, 1, &z);
	writeMAG3110(MAG3110Map::OFF_Y_LSB, 1, &z);
	writeMAG3110(MAG3110Map::OFF_Y_MSB, 1, &z);
	writeMAG3110(MAG3110Map::OFF_Z_LSB, 1, &z);
	writeMAG3110(MAG3110Map::OFF_Z_MSB, 1, &z);
//	printf("ABC\n");
	// configure
//	for(int k=0; k<10; k++)
//	{
//	readMAG3110(k,1,&whoamI);
//	printf("k%d: %x\n",k,whoamI);
//	}
}


void MAG3110::readMags(MagVector *mag)
{
	short magX;
	short magY;
	short magZ;
//	printf("StartM\n");
	char msbX, msbY, msbZ, lsbX, lsbY, lsbZ;

	readMAG3110( MAG3110Map::OUT_X_MSB,1, &msbX);
	readMAG3110(MAG3110Map::OUT_X_LSB, 1, &lsbX);
	readMAG3110(MAG3110Map::OUT_Y_MSB, 1, &msbY);
	readMAG3110(MAG3110Map::OUT_Y_LSB, 1, &lsbY);
	readMAG3110(MAG3110Map::OUT_Z_MSB, 1, &msbZ);
	readMAG3110(MAG3110Map::OUT_Z_LSB, 1, &lsbZ);

	magX = (msbX << 8) + lsbX;
	magY = (msbY << 8) + lsbY;
	magZ = (msbZ << 8) + lsbZ;

	if (rawEn)
	{
		// X and Z are swapped on Mag3110 compared to HMC
		mag->magx = magX * RAW_MAG3110_TO_uT;
		mag->magy = magY * RAW_MAG3110_TO_uT;
		mag->magz = magZ * RAW_MAG3110_TO_uT;

//		printf("Mag2: %x %x %x\n", magX,magY,magZ);
//		printf("Mag2: %f %f %f\n", mag->magx, mag->magy, mag->magz);
	}
	else
	{
	}
//	printf("EndMag\n");
	//readStatus();
}


bool MAG3110::magWaiting()
{
	return true;
}

void MAG3110::readStatus()
{
	char data;
	readMAG3110(MAG3110Map::DR_STATUS, 1, &data);
	printf("Mag %x\n",data);
}
// ----- utitlity methods -----
void MAG3110::linkI2cBus(I2C_Device *dev)
{
	i2cBus = dev;
}


void MAG3110::readMAG3110(unsigned int reg, unsigned int totalReg, char *data)
{
	i2cBus->readI2c(MAG3110Map::deviceId, reg, totalReg, data);
//	printf("Mag: %x\n",*data);
}


void  MAG3110::writeMAG3110(unsigned int reg, unsigned int totalReg, char *data)
{
	i2cBus->writeI2c(MAG3110Map::deviceId, reg, totalReg, data);
}
