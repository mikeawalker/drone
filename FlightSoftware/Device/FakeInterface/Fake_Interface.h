#ifndef Fake_Interface_H
#define Fake_Interface_H

#include "Block.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "GpsPvtMsg.h"
#include "MyTime.h"
#include "Defines.h"
#include "MagInterrupt.h"
//out
#include "ImuMsg.h"
#include "MagMsg.h"
#include "GpsAccelMsg.h"


class Fake_Interface : public Block
{
public:
	Fake_Interface(std::string bName );
	~Fake_Interface( );
	void update();
	void CheckSend();
private:


	bool firstMeasure;
	boost::posix_time::ptime  currTime_;
	boost::posix_time::ptime  firstTime_;
	GpsPvtMsg gpsMsg_;
	MagInterrupt magWaitingMsg_;
	ImuMsg imuMsg_;
	MagMsg magMsg_;
	GpsAccelMsg gpsAccelMsg_;
	unsigned int msCtr;
	static const unsigned int GPS_NUM =  100;
protected:

};
#endif