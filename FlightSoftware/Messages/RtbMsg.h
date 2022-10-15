#ifndef RtbMsg_H
#define RtbMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class RtbMsg : public Message 
{
public: 
	RtbMsg();
	 ~RtbMsg();
	bool getData(ReturnToBase *data);
	bool setData(ReturnToBase *data);
	ReturnToBase myData;
private:
protected:
};
#endif