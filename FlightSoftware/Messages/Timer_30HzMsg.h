#ifndef Timer_30HzMsg_H
#define Timer_30HzMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class Timer_30HzMsg : public Message 
{
public: 
	Timer_30HzMsg();
	 ~Timer_30HzMsg();
	bool getData(bool *data);
	bool setData(bool *data);
	bool myData;
private:
protected:
};
#endif