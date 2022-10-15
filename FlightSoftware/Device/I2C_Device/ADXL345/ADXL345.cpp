#include "ADXL345.h"



ADXL345::ADXL345()
{
}


ADXL345::~ADXL345()
{

}

void ADXL345::linkI2cBus(I2C_Device *dev)
{
	i2cBus = dev;
}

// --- Reading Accels function ---//

bool ADXL345::accelsWaiting()
{
	char status;
	readADXL345( ADXL345Map::FIFO_STATUS , 1 ,  &status);
	entriesWaiting = (int)( status & 0x3F);
	//printf("A: %d\n", entriesWaiting);
	return entriesWaiting > 0;
}

void ADXL345::readAccels( AccelVector *aout )
{
	short accelX;
	short accelY;
	short accelZ;
	// we have to grab all the bytes at once so we don't get overrun;
	readADXL345( ADXL345Map::DATAX0, 6 ,  accelData);
	// put the shorts together
	accelX = ( accelData[1] << 8 ) + accelData[0];
	accelY = ( accelData[3] << 8 ) + accelData[2];
	accelZ = ( accelData[5] << 8 ) + accelData[4];
	// change the shorts into engineering units
	aout->ax = ( accelX *  gScaleFactor ) * G0 ;
	aout->ay = ( accelY *  gScaleFactor ) * G0 ;
	aout->az = ( accelZ *  gScaleFactor ) * G0 ;
}

//
void ADXL345::setupDevice()
{
	char ofsX,ofsY,ofsZ;
	
	// setup data format
	setupDataFormat( ADXL345_Settings::RANGE_8G_PM , true );
	// setup rate 
	setupRate( ADXL345_Settings::RATE_100 , true );
	// setup offsets
	setupOffsets( 0.0 , 0.0 , 0.0 );
	// setup fifo 
	setupFifo( ADXL345_Settings::FIFO_STREAM ); // stream mode (last 32 samples);
	//power on
	setupPowerControl(true);
        char r1;
	readADXL345( ADXL345Map::POWER_CTL,1,&r1);
	printf("R: %x\n",r1);
}


void ADXL345::readADXL345(unsigned int reg, unsigned int totalReg, char *data)
{
	//may need to do an rw bit
	i2cBus->readI2c( ADXL345Map::deviceId , reg , totalReg , data );

}


void ADXL345::writeADXL345(unsigned int reg, unsigned int totalReg, char *data)
{
	//may need to do a rw bit
	i2cBus->writeI2c( ADXL345Map::deviceId , reg , totalReg , data );
}

// ---------------- OFFSETS Setup ------------------------
void ADXL345::setupOffsets(float off_x , float off_y, float off_z)
{
	char x,y,z;
	

	x = calcOffsetByte( off_x );
	y = calcOffsetByte( off_y );
	z = calcOffsetByte( off_z );


	writeADXL345( ADXL345Map::OFSX , 1 , &x );
	writeADXL345( ADXL345Map::OFSY , 1 , &y );
	writeADXL345( ADXL345Map::OFSZ , 1 , &z );
}



char ADXL345::calcOffsetByte( float offset )
{
	char byte;
	short bits;
	bits = static_cast<short>( offset * ADXL345_Settings::OFFSET_SCALE );
	byte = (char)( bits );
	return byte;
}

// ------------ Rate Setup ---------------
void  ADXL345::setupRate(unsigned char rate, bool lowPowerOn)
{
	char byte = 0x00;
	if( lowPowerOn )
	{
		// low power only has 12.5 -> 400 hz
		if( rate > ADXL345_Settings::RATE_400 )
		{
			rate = ADXL345_Settings::RATE_400;
		}
		else if( rate < ADXL345_Settings::RATE_12p5 ) 
		{
			rate = ADXL345_Settings::RATE_12p5;
		}

	}
	
	byte |=  ( lowPowerOn ? 0 : 1) << 4;
	byte |=  rate;
	writeADXL345( ADXL345Map::BW_RATE  ,  1 , &byte );

	
}

//----- Setup data formatting ------//
void ADXL345::setupDataFormat(unsigned char range, bool fullRes)
{
	char byte = 0x0;
	float totRange;
	byte |=  range; // these are the 0 ,1 bits
	byte |= ( fullRes ? 1 : 0  ) << 3 ; // bit 4 is the full res bit
	// bit 7 is self test bit --- leave as 0
	// bit 6 is the spi bit ... default to 4 wire spi
	// bit 5 is int invert bit leave as active high
	// bit 3 is justify bit leave at 0 for right justify
	writeADXL345( ADXL345Map::DATA_FORMAT  ,  1 , &byte );
	
	if( fullRes  )
	{
		gScaleFactor =  ADXL345_Settings::FULL_RES_SCALE;
	}
	else 
	{
		
		totRange = 2*std::pow( 2.0 , (int)(range)+1);//total range (+-16 = 32 ) 
		gScaleFactor = range / std::pow(2.0,10.0);
	}
}


// ----- Setup FIFO ----------//
void ADXL345::setupFifo( unsigned char fifoMode)
{
	char byte = 0x0;
	
	// set the mode
	byte |= ( fifoMode <<  6 );
	// leave trigger bit at 0 / interrupt 1
	//let 1 sample trigger the watermark interrupt
	byte |= 0x1; 

	writeADXL345( ADXL345Map::FIFO_CTL ,  1 , &byte );
}

// Power Control

void ADXL345::setupPowerControl(bool powerOn)
{
	char power = 0;
	//link bit set to 0 (bit 5)
	//autosleep bit set to 0 (bit 4)
	
	//set measurebit (bit 3)
	power |= ( powerOn ? 1 : 0 ) << 3;
	
	//sleep bit set to 0 
	//wakeupbits set to 0
	writeADXL345( ADXL345Map::POWER_CTL , 1 , &power);
}
