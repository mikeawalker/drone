#include "Radio3dr.h"
#include "Structs.h"


Radio3dr::Radio3dr():
myStream(true)
{

}

Radio3dr::~Radio3dr()
{

}
void Radio3dr::linkSerial(SerialDevice *dev)
{
	//myStream.initialize(300);
	mySerial_ = dev;
}

void Radio3dr::setupRadio()
{

}

void Radio3dr::readRadio()
{
	int bytes;
	bool ok;
	bytes = mySerial_->readSerial(buff, 300);
	while (bytes > 0)
	{

		myStream.append(buff, bytes);
//		printf("GPS MSG: %s\n", buff);
		myStream.parseAll();
		bytes = mySerial_->readSerial(buff, 300);
		//
	}

}


bool  Radio3dr::getOutput(BeatTime &cmd)
{

	return myStream.pullHeartBeat(cmd);
}

bool Radio3dr::getOutput(UserCmd &cmd)
{
	return myStream.pullCommand(cmd);
}

bool Radio3dr::getOutput(FullState &cmd)
{
	return myStream.pullState(cmd);
}

void Radio3dr::sendMsg(FullState &in)
{
	std::string out; 
	myStream.formatMsg(&in, sizeof(double)* 17, LINK_EKF);
	out = myStream.getOutMsg();
	mySerial_->writeSerial((char *)out.c_str(), out.size());
	//std::cout << std::endl;
	//std::cout << "Wrote: " << out.size() << " Msg:" << out << std::endl;
}

void Radio3dr::sendMsg(ImuMeasurement &in)
{
	std::string out;
	myStream.formatMsg(&in, sizeof(double)* 7, LINK_IMU);
	out = myStream.getOutMsg();
	mySerial_->writeSerial((char *)out.c_str(), out.size());
	//std::cout << std::endl;
	//std::cout << "Wrote: " << out.size()<< " Msg:" << out << std::endl;
}

void Radio3dr::sendMsg(void *data, std::string type, int size)
{
	std::string out;
	myStream.formatMsg(data, size, type);
	out = myStream.getOutMsg();
	mySerial_->writeSerial((char*)out.c_str(), out.size());


}
