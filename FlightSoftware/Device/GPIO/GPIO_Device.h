#ifndef GPIO_DEVICE_H
#define GPIO_DEVICE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>

#include "Defines.h"
#include "Structs.h"
#include "XPlatform.h"


#ifdef LINUX_DEVICE
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#else

#endif


class GPIO_Device
{
public:
	GPIO_Device(std::string pinNum);
	GPIO_Device(std::string pinNum, std::string dir);
	~GPIO_Device();
	bool enable();
	bool disable( );
	bool write(std::string val);
	bool setDirection(std::string inOut);
	bool setEdge(std::string edgeTpye);
	int getFd();
	unsigned int read( );

	std::string gpioFile;
	
private:
	std::string myPin;
	
	std::string gpioBase;
	std::string gpioEnable;
	std::string gpioDisable;
	std::string dirName;
	std::string edgeName;
	std::string valName;

	std::ofstream exportgpio;
	std::ofstream unexportgpio;
	
	int fd;

protected:

};

#endif
