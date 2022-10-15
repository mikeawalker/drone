#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include "Block.h"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "GpsPvtMsg.h"
#include "GpsAccelMsg.h"
#include "UserCmdMsg.h"

#include "EkfStateMsg.h"
#include "TmHeartBeat.h"
#include "MyTime.h"
#include "GPIO_Device.h"
#include "SerialDevice.h"
#include "Defines.h"
#include <queue>
#include "LS20031.h"
#include "Timer.h"

class Serial_Interface : public Block
{
public:
	Serial_Interface(std::string bName );
	~Serial_Interface( );
	void update();
	void CheckSend();
	void CheckMessages();
private:

	void ReCalcAccel();
	LS20031 myGpsDevice_;
	
	bool firstMeasure;
	boost::posix_time::ptime  currTime_;
	boost::posix_time::ptime  firstTime_;
	GpsPvtMsg gpsMsg_;
	GpsAccelMsg gpsAccelMsg_;
	UserCmdMsg userCmdMsg_;
	EkfStateMsg StateMsg;
	TmHeartBeat heatBeatMsg_;
	unsigned int msCtr;

	GPIO_Device gpsPower_;
	
	SerialDevice mySerial_;
	
	static const unsigned int GPS_NUM =  100;

	std::deque<double> xQueue;
	std::deque<double> yQueue;
	std::deque<double> zQueue;
	std::deque<double> tQueue;

	Timer myTimer;
	FullState myState;
protected:

};
#endif