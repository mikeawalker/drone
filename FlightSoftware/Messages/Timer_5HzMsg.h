#ifndef Timer_5HzMsg_H
#define Timer_5HzMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class Timer_5HzMsg : public Message 
{
public: 
	Timer_5HzMsg();
	 ~Timer_5HzMsg();
	bool getData(bool *data);
	bool setData(bool *data);
	bool myData;
private:
protected:
};
#endif