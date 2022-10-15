#ifndef WaypointMsg_H
#define WaypointMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class WaypointMsg : public Message 
{
public: 
	WaypointMsg();
	 ~WaypointMsg();
	bool getData(WaypointLocation *data);
	bool setData(WaypointLocation *data);
	WaypointLocation myData;
private:
protected:
};
#endif