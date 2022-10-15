#ifndef RADIO_INTERFACE_H
#define RADIO_INTERFACE_H

#include "Block.h"
#include "boost/date_time/posix_time/posix_time.hpp"



#include "EkfStateMsg.h"
#include "ImuMsg.h"
#include "MagMsg.h"
#include "GpsPvtMsg.h"
#include "TmHeartBeat.h"
#include "UserCmdMsg.h"
#include "MyTime.h"
#include "GPIO_Device.h"
#include "SerialDevice.h"
#include "Defines.h"
#include <queue>
#include "Radio3dr.h"
#include "Timer.h"

class Radio_Interface : public Block
{
public:
	Radio_Interface(std::string bName , int tmMode );
	~Radio_Interface();
	void update();
	void CheckSend();
	void CheckMessages();
	void CheckRadio();
private:

	void ReCalcAccel();
	Radio3dr myRadio_;
	
	bool firstMeasure;
	boost::posix_time::ptime  currTime_;
	
	EkfStateMsg stateMsg;
	ImuMsg imuMsg;
	MagMsg magMsg;
	TmHeartBeat heartBeatMsg_;
	UserCmdMsg cmdMsg_;
	GpsPvtMsg gpsMsg;
	unsigned int msCtr;

	
	SerialDevice mySerial_;

	//Timer myTimer;

protected:

};
#endif