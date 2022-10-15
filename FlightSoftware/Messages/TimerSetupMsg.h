#ifndef TimerSetupMsg_H
#define TimerSetupMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class TimerSetupMsg : public Message 
{
public: 
	TimerSetupMsg();
	 ~TimerSetupMsg();
	bool getData(TimerSetup *data);
	bool setData(TimerSetup *data);
	TimerSetup myData;
private:
protected:
};
#endif