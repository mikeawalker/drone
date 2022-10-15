#ifndef LS20031_H
#define LS20031_H

#include "SerialDevice.h"
#include "XPlatform.h"
#include "NmeaStream.h"
#include "Structs.h"
#include <string>
class LS20031
{
public:
	LS20031();
	~LS20031();
	void setupGps();
	void linkSerial(SerialDevice *dev);
	void readGps();

	bool getPvt(GpsMeasurement *pvt);
private:
	std::string setupRate_;
	std::string setupOutput_;

	SerialDevice *mySerial_;
	char buff[300];
	bool posFixRdy_;
	NmeaStream myStream;
protected:
};
#endif