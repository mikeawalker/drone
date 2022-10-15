#include "GPIO_Device.h"


GPIO_Device::GPIO_Device(std::string pinNum)
{
	
#ifdef LINUX_DEVICE
	gpioBase = "/sys/class/gpio/gpio";
	gpioEnable = "/sys/class/gpio/export";
	gpioDisable = "/sys/class/gpio/unexport";
#else
	gpioBase = "./gpio";
	gpioEnable = "./gpio/export";
	gpioDisable = "./gpio/unexport";

#endif
	myPin = pinNum;
	enable();
}


GPIO_Device::GPIO_Device(std::string pinNum , std::string dir)
{

#ifdef LINUX_DEVICE
	gpioBase = "/sys/class/gpio/gpio";
	gpioEnable = "/sys/class/gpio/export";
	gpioDisable = "/sys/class/gpio/unexport";
#else
	gpioBase = "./gpio";
	gpioEnable = "./gpio/export";
	gpioDisable = "./gpio/unexport";

#endif
	myPin = pinNum;
	enable();

	setDirection(dir);
}


GPIO_Device::~GPIO_Device()
{
	disable();
}


bool GPIO_Device::enable()
{

	//exportgpio.close();

	FILE *fd;
	int pin;
		

	// Export the pin and set direction to input

	if ((fd = fopen(gpioEnable.c_str(), "w")) == NULL)
	{
		fprintf(stderr, " Unable to open GPIO export interface: %s\n", strerror(errno));
		exit(1);
	}

	fprintf(fd, "%s\n", myPin.c_str());
	fclose(fd);

	return true;
}
bool GPIO_Device::disable()
{
	
	FILE *fd;
	fd = fopen( gpioDisable.c_str() , "w" );
	if ( fd  < 0)
	{
		std::cout << " Disable GPIO Failed: " << gpioDisable<< std::endl;
		return false;
	}
	fprintf(fd, "%s\n", myPin.c_str());

	fclose(fd);
	return true;
}
bool GPIO_Device::write(std::string val)
{

	setDirection(GPIO_OUT);
	std::ofstream gpioOut(valName.c_str(), std::ofstream::out);
	if (XPlatform::BadFile(&gpioOut)){
		std::cout << "GPIO WRITE ERROR: " << valName<< std::endl;
		return false;
	}
	gpioOut << val;
	gpioOut.close();
	return true;
}
unsigned int GPIO_Device::read()
{
	setDirection(GPIO_IN);
	unsigned int val;
	std::string a;
	valName = gpioBase + myPin + "/" + "value";
	//std::cout << "GPIO FNAME: " << valName << std::endl;
	std::ifstream gpioIn(valName.c_str(), std::ifstream::out);
	if (XPlatform::BadFile(&gpioIn)){
		std::cout << "GPIO READ ERROR: " << valName<< std::endl;
		return -1;
	}
	gpioIn >> val;
	
	//std::cout << "ReadVal: " << a << " :Read Done" << std::endl;
	gpioIn.close();
	
	return val;
}



bool GPIO_Device::setDirection(std::string inOut)
{
	std::ofstream gpioDirect(dirName.c_str(), std::ofstream::out);
	std::cout << "Direction: " << dirName << " " << inOut << std::endl;
	if ( XPlatform::BadFile(&gpioDirect) )
	{
		std::cout << " Direction GPIO Failed: " << dirName<< std::endl;
		return false;
	}
	gpioDirect << inOut;
	gpioDirect.close();
	return true;
}


bool GPIO_Device::setEdge(std::string edge)
{
	std::ofstream gpioEdge(edgeName.c_str(), std::ofstream::out);
    std::cout << " Edge:  " << edgeName << " " << edge << std::endl;
	if (XPlatform::BadFile(&gpioEdge))
	{
		std::cout << " Edge GPIO Failed " << edgeName << std::endl;
		return false;
	}
	gpioEdge << edge;
	gpioEdge.close();
	return true;
}

int GPIO_Device::getFd()
{
	valName = gpioBase + myPin + "/" + "value";
	std::cout << "ValName: " << valName << std::endl;
#ifdef LINUX_DEVICE
	fd = open(valName.c_str(), O_RDONLY | O_NONBLOCK);
#endif
	if (fd < 0)
	{
		std::cout << "Fd Open Fail " << valName  << " " << fd<< std::endl;
		perror("gpio/fd_open");
	}
	return fd;
}