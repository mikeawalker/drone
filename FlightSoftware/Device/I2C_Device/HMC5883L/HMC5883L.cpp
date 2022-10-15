#include "HMC5883L.h"


const double HMC5883L::GAUSS_TO_uTESLA =100;

HMC5883L::HMC5883L()
{

}

HMC5883L::~HMC5883L()
{
}

// ----- utitlity methods -----
void HMC5883L::linkI2cBus(I2C_Device *dev)
{
	i2cBus = dev;
}


void HMC5883L::readHMC5883L(unsigned int reg , unsigned int totalReg , char *data) 
{
	i2cBus->readI2c( HMC5883LMap::deviceId, reg , totalReg , data  );
}


void  HMC5883L::writeHMC5883L(unsigned int reg , unsigned int totalReg , char *data) 
{
	i2cBus->writeI2c( HMC5883LMap::deviceId , reg , totalReg , data);
}

// --- setup metods ---- //


void HMC5883L::setupDevice()
{

	scaleX = 1.0;
	scaleY = 1.0;
	scaleZ = 1.0;
//	magBalance();

	HMC5883L_Settings::MagSetup setupData;
	setupData.avg = HMC5883L_Settings::AVG_1;
	setupData.mode = HMC5883L_Settings::MODE_NORMAL;
	//setupData.rate = HMC5883L_Settings::RATE_30_Hz;
	setupData.rate = HMC5883L_Settings::RATE_3_Hz;

	setupData.gainInd = HMC5883L_Settings::PM_1p9_Gauss; // earth mag field ~.2-.6 G on surface
	// write configuration registers
	magConfig(setupData);
	//write mode register for continuous measurements
	outputConfig( HMC5883L_Settings::MEASURE_CONT );
	MagVector temp;
	for(int k=0;k<2;k++){
		MyTime::mSleep(330);
	
	readMags(&temp);
	printf("%f %f %f\n",temp.magx,temp.magy,temp.magz);
	}
	
	
}

void HMC5883L::magConfig(HMC5883L_Settings::MagSetup setup)
{
	char configA=0x00;
	char configB=0x00;
	/* --------- write config register A -------------*/

	// bit 7 is reserved
	// bit 5-6 number of samples to be averaged per measurement
	configA |= ( setup.avg << 5 ) & 0x60;
	// bit 2-4 data output rate
	configA |= ( setup.rate << 2 ) & 0x1C;
	// bits 0-1 are measurement flow
	configA |= (setup.mode ) & 0x3;
	/* -----------write config regsiter B   ------------*/
	//bits 0-4 must be kept clear
	//bits 5-7 are gain configuration bits
	configB |=  (HMC5883L_Settings::gainTable[ setup.gainInd].gainSetting << 5) &  0xE0;//map in top 3 bits
	// send settings
	writeHMC5883L(HMC5883LMap::CfgA , 1 , &configA);
	writeHMC5883L(HMC5883LMap::CfgB , 1 , &configB);
	//printf("HMC: %x %x\n", configA, configB);
	magScaleFactor = 1.0/( HMC5883L_Settings::gainTable[ setup.gainInd ].gain );
}


void HMC5883L::outputConfig( unsigned char mode )
{
	char byte = 0x00;

	byte |= ( mode )  & 0x03;
	writeHMC5883L(HMC5883LMap::Mode , 1 , &byte);
}


void HMC5883L::getStatus()
{
	char status;
	readHMC5883L(HMC5883LMap::Status , 1 , &status);

	rdyBit_ = ( status & 0x01 ) == 1;
	lockBit_ = (( status & 0x02 ) >> 1 ) ==1;
	//printf("Stat: %x \n" , status);
}


bool HMC5883L::magsWaiting()
{
	getStatus();

	if( lockBit_ )
	{
//		printf("Unexpected Mag Lock Bit\n");
	}
	return rdyBit_;
}


void HMC5883L::readMags(MagVector *mout)
{
	short magX,magY,magZ;
	int clear=0;
//	i2cBus->pointI2C( HMC5883LMap::deviceId ,  HMC5883LMap::DataXMSB ) ;

	readHMC5883L( HMC5883LMap::DataXMSB , 6 , magVec );


	// the order of bytes is xMSB,xLSB,zMSB,zLSB,yMSB,yLSB
	magX =  ( magVec[0] << 8 ) + magVec[1];
	magY =  (magVec[4] <<8 ) + magVec[5];
	magZ = (magVec[2] <<8 ) + magVec[3];

	
	mout->magx = magX * magScaleFactor * scaleX*GAUSS_TO_uTESLA;
	mout->magy = magY * magScaleFactor * scaleY*GAUSS_TO_uTESLA;
	mout->magz = magZ * magScaleFactor * scaleZ*GAUSS_TO_uTESLA;
//	printf("M: %f %f %f\n", mout->magx , mout->magy , mout->magz );
	getStatus();

}


void HMC5883L::magBalance()
{
	HMC5883L_Settings::MagSetup setupData;
	MagVector temp;


	scaleX = 1.0;
	scaleY = 1.0;
	scaleZ = 1.0;

	setupData.avg = HMC5883L_Settings::AVG_1;
	setupData.mode = HMC5883L_Settings::MODE_POSBIAS;
	//setupData.rate = HMC5883L_Settings::RATE_30_Hz;
	setupData.rate = HMC5883L_Settings::RATE_3_Hz;

	setupData.gainInd = HMC5883L_Settings::PM_1p9_Gauss; // earth mag field ~.2-.6 G on surface
	// write configuration registers
	magConfig(setupData);
	//write mode register for continuous measurements
	outputConfig(HMC5883L_Settings::MEASURE_CONT);

	// sleep 
	MyTime::mSleep(330);
	//
	readMags(&temp);
	printf("%f %f %f\n", temp.magx, temp.magy, temp.magz);
//	usleep(330000);
//	readMags(&temp);
//	printf("%f %f %f\n", temp.magx, temp.magy, temp.magz);
	for( int k=0;k<10;k++){
		MyTime::mSleep(330);
		
		readMags(&temp);
		printf("%f %f %f\n", temp.magx , temp.magy , temp.magz);
	}
	
	scaleX =  temp.magx / 1.16;
	scaleY =  temp.magy / 1.16;
	scaleZ =  temp.magz / 1.08;
	printf("Mag Scales: %f %f %f\n",scaleX,scaleY,scaleZ);
}
