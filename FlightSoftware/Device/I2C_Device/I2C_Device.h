#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include "Defines.h"
#include "Structs.h"

//#define LINUX_I2C

#ifdef LINUX_DEVICE
//#include <glib.h>
//#include <glib/gprintf.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#else

#endif


class I2C_Device
{
public:
	I2C_Device();
	~I2C_Device();
	bool readI2c( unsigned char devAddr, unsigned char reg ,  int nBytes , char *data);
	bool writeI2c( unsigned char devAddr , unsigned char reg ,  int nBytes, char *data);
	void pointI2C( unsigned char devAddr , unsigned char reg );
	bool openI2c(std::string deviceFile);
	void closeI2c();
private:
	int i2cFile;
	unsigned char currentDevAddr;

protected:

};

#endif
