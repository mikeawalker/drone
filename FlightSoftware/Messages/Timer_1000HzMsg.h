#ifndef Timer_1000HzMsg_H
#define Timer_1000HzMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class Timer_1000HzMsg : public Message 
{
public: 
	Timer_1000HzMsg();
	 ~Timer_1000HzMsg();
	bool getData(bool *data);
	bool setData(bool *data);
	bool myData;
private:
protected:
};
#endif