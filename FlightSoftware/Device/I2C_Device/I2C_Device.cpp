#include "I2C_Device.h"
//see gnublin drivers as exa,[;e
I2C_Device::I2C_Device()
{
	i2cFile = 0;
}

I2C_Device::~I2C_Device()
{
}

#ifdef LINUX_DEVICE

void I2C_Device::closeI2c()
{
	if( i2cFile )
	{
		printf("CLOSING\n");
		close(i2cFile);
		i2cFile = 0;
	}
}
bool I2C_Device::openI2c(std::string deviceFile)
{

	bool result;
	printf("Linux I2C\n");
	if( i2cFile ) 
	{
		closeI2c();
	}
	printf("TOALLY\n");
	std::cout<<"ABC"<<deviceFile<<std::endl;
	i2cFile = open( deviceFile.c_str() , O_RDWR );	
	printf("CC\n");
	if( i2cFile < 0 )
	{
		printf("Errror I2C Fail");
		return false;
	}
	return true;
}

bool I2C_Device::readI2c( unsigned char devAddr , unsigned char reg ,  int nBytes , char *data)
{
	int rcvBytes;
	if( devAddr != currentDevAddr )
	{
		ioctl(i2cFile, I2C_SLAVE, devAddr);
		currentDevAddr = devAddr;
	}

	// 
	if( write( i2cFile , &reg , 1)  != 1 )
	{
		printf("i2c write error in read fcn %x\n" , devAddr );
		return false;
	}
	// read from i2c file
	rcvBytes = read( i2cFile , data , nBytes );
	if( rcvBytes != nBytes )
	{
		printf("i2c read error in read fcn %x\n" , devAddr);
		return false;
	}

	return true;
}


bool I2C_Device::writeI2c(  unsigned char devAddr , unsigned char reg , int nBytes, char *data)
{
	bool success;
	int writeBytes;
	unsigned char dataOut[nBytes + 1];
	dataOut[0] = reg;
	memcpy( &dataOut[1] , data , nBytes);
	
	if( devAddr != currentDevAddr )
	{
		ioctl(i2cFile, I2C_SLAVE, devAddr);
		currentDevAddr = devAddr;
	}


	writeBytes = write( i2cFile , dataOut , nBytes+1 );
	success = (writeBytes  == nBytes+1 );
	if( !success )
	{
		printf("I2C Write error in sendI2c %d %d\n", nBytes , writeBytes);
	}
	return success;

}

void I2C_Device::pointI2C( unsigned char devAddr , unsigned char reg )
{
	bool success;
	int writeBytes;
	unsigned char dataOut[2];

	dataOut[0] = devAddr;
	dataOut[1] = reg;
	if( devAddr != currentDevAddr )
	{
		ioctl(i2cFile, I2C_SLAVE, devAddr);
		currentDevAddr = devAddr;
	}
	writeBytes = write( i2cFile , dataOut , 2 );
	printf("%x %x\n", dataOut[0] , dataOut[1]);
	success = (writeBytes  == 2 );
	if( !success )
	{
		printf("I2C Point error in sendI2c %d %d\n", 2 , writeBytes);
	}
}

#else




bool I2C_Device::readI2c(unsigned char devAddr, unsigned char reg,  int nBytes, char *data)
{
	char z=0;
	for( int x = 0 ; x < nBytes ; x++)
	{
		memcpy( &data[x] ,&z , 1);
	}
	return true;
}

bool I2C_Device::writeI2c(unsigned char devAddr, unsigned char reg,  int nBytes, char *data)
{
	return true;
}

bool I2C_Device::openI2c(std::string deviceFile)
{
 return true;
}

#endif
