#ifndef ImuMsg_H
#define ImuMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class ImuMsg : public Message 
{
public: 
	ImuMsg();
	 ~ImuMsg();
	bool getData(ImuMeasurement *data);
	bool setData(ImuMeasurement *data);
	ImuMeasurement myData;
private:
protected:
};
#endif