#ifndef StabilityMsg_H
#define StabilityMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class StabilityMsg : public Message 
{
public: 
	StabilityMsg();
	 ~StabilityMsg();
	bool getData(StabilityCmd *data);
	bool setData(StabilityCmd *data);
	StabilityCmd myData;
private:
protected:
};
#endif