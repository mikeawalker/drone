#include "SerialDevice.h"

SerialDevice::SerialDevice()
{

}
SerialDevice::~SerialDevice()
{
	Close();
}
bool SerialDevice::Open(std::string dev)
{
#ifdef LINUX_DEVICE
	serialFile_ = open(dev.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
#else
	serialFile_.open("GpsSerial.txt");
#endif
	if (XPlatform::BadFile(&serialFile_))
	{
		std::cout << "Serial File Not Open:  " << dev << std::endl;
		return false ;
	}


	return true;
}
void SerialDevice::Close()
{
#ifdef LINUX_DEVICE

#else
	serialFile_.close();
#endif
}
void SerialDevice::writeSerial(char *ptr, int bytes)
{
	int count;
#ifdef LINUX_DEVICE
	count = write(serialFile_, ptr, bytes);
	//printf("Serial write %d \n",count);
#else
		//serialFile_.write(ptr, bytes);
#endif
}
unsigned int SerialDevice::readSerial(char *ptr, int maxBytes)
{
	int bytesRead;
#ifdef LINUX_DEVICE
	bytesRead = read(serialFile_, (void*)ptr, maxBytes);
	//std::cout<<"Bytes: "<<bytesRead<<std::endl;
#else
	//bytesRead = serialFile_.readsome(ptr, maxBytes);
	bytesRead = readSome(ptr, maxBytes);
	
	//std::cout<<"Bytes: "<<bytesRead<<std::endl;
#endif
	return bytesRead;
}


void SerialDevice::Configure(int baud)
{
#ifdef LINUX_DEVICE
	struct termios options;
	tcgetattr(serialFile_, &options);
	options.c_cflag = B57600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(serialFile_, TCIFLUSH);
	tcsetattr(serialFile_, TCSANOW, &options);


#endif
}

void SerialDevice::Clear()
{
#ifdef LINUX_DEVICE
	tcflush(serialFile_, TCIOFLUSH);
#else

#endif
}




int SerialDevice::readSome(char *ptr, int maxBytes)
{
	int bytesRead;
#ifdef LINUX_DEVICE
	bytesRead = read(serialFile_, ptr, maxBytes);
#else
	serialFile_.getline(ptr, maxBytes);
	bytesRead = serialFile_.gcount();
#endif
	return bytesRead;
}
