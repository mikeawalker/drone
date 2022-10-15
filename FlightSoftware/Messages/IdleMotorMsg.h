#ifndef IdleMotorMsg_H
#define IdleMotorMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class IdleMotorMsg : public Message 
{
public: 
	IdleMotorMsg();
	 ~IdleMotorMsg();
	bool getData( IdleCmd *data);
	bool setData( IdleCmd *data);
	 IdleCmd myData;
private:
protected:
};
#endif