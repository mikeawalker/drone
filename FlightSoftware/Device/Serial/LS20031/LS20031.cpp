#include "LS20031.h"



LS20031::LS20031()
{

}

LS20031::~LS20031()
{

}

void LS20031::setupGps()
{
	setupRate_ = "$PMTK220,1000*1F\r\n";
	setupOutput_ = "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n";
	mySerial_->writeSerial("$PMTK220,1000*1F\r\n", setupRate_.size());
	mySerial_->writeSerial("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n", setupOutput_.size());
}
void LS20031::linkSerial(SerialDevice *dev)
{
	myStream.initialize(300);
	mySerial_ = dev;
}


void LS20031::readGps()
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


bool LS20031::getPvt(GpsMeasurement *pvt)
{
	
	return	myStream.getPVT(pvt);
}
