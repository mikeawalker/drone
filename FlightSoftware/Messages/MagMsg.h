#ifndef MagMsg_H
#define MagMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class MagMsg : public Message 
{
public: 
	MagMsg();
	 ~MagMsg();
	bool getData(MagMeasurement *data);
	bool setData(MagMeasurement *data);
	MagMeasurement myData;
private:
protected:
};
#endif