#ifndef GpsAccelMsg_H
#define GpsAccelMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class GpsAccelMsg : public Message 
{
public: 
	GpsAccelMsg();
	 ~GpsAccelMsg();
	bool getData( AccelVector *data);
	bool setData( AccelVector *data);
	 AccelVector myData;
private:
protected:
};
#endif