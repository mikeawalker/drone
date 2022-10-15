#ifndef SERIALDEVICE_H
#define SERIALDEVICE_H

#include <string>
#include <fstream>
#include <iostream>
#include "XPlatform.h"
#include <stdio.h>

#include <fcntl.h>			//Used for UART
#ifdef LINUX_DEVICE 
	#include <termios.h>		//Used for UART
	#include <unistd.h>			//Used for UART
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

class SerialDevice
{
public:
	SerialDevice();
	~SerialDevice();
	bool Open(std::string dev);
	void Close();
	void Configure(int baud);
	void writeSerial(char *ptr, int bytes);
	unsigned int readSerial(char *ptr, int maxBytes);
	void Clear();
private:
	int readSome(char *ptr, int maxBytes);
	std::string myDev_;
#ifdef LINUX_DEVICE
	int serialFile_;
#else
	std::ifstream serialFile_;
#endif
protected:
};
#endif