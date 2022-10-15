#ifndef RADIO3DR_H
#define RADIO3DR_H

#include "SerialDevice.h"
#include "XPlatform.h"
#include "Structs.h"
#include "GroundStream.h"
#include <string>
class Radio3dr
{
public:
	Radio3dr();
	~Radio3dr();
	void setupRadio();
	void radioDebugMenu();
	void readRadio();

	void linkSerial(SerialDevice *dev);

	bool getOutput(FullState &state);
	bool getOutput(UserCmd &cmd);
	bool getOutput(	BeatTime &cmd);
	void sendMsg(FullState &in);
	void sendMsg(ImuMeasurement &in);
	void sendMsg(void *data, std::string type, int size);
private:
	std::string setupRate_;
	std::string setupOutput_;

	SerialDevice *mySerial_;

	GroundStream myStream;
	char buff[300];
	bool posFixRdy_;
protected:
};
#endif