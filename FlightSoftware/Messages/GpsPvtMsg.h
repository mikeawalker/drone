#ifndef GpsPvtMsg_H
#define GpsPvtMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class GpsPvtMsg : public Message 
{
public: 
	GpsPvtMsg();
	 ~GpsPvtMsg();
	bool getData(GpsMeasurement *data);
	bool setData(GpsMeasurement *data);
	GpsMeasurement myData;
private:
protected:
};
#endif