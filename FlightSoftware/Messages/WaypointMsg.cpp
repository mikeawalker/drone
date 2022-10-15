#include "WaypointMsg.h"
WaypointMsg::WaypointMsg() : Message( sizeof( WaypointLocation ) )
{
	myHeader.dataSize = sizeof(WaypointLocation);
	myHeader.messageId = DroneMsgTypes::WaypointMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
WaypointMsg::~WaypointMsg()
{

}
bool WaypointMsg::getData(WaypointLocation *data)
{
	*data = myData;
	 return true;
}
bool WaypointMsg::setData(WaypointLocation *data)
{
	myData = *data;
	 return true;
}
