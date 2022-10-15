#include "GpsAccelMsg.h"
GpsAccelMsg::GpsAccelMsg() : Message( sizeof(  AccelVector ) )
{
	myHeader.dataSize = sizeof( AccelVector);
	myHeader.messageId = DroneMsgTypes::GpsAccelMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
GpsAccelMsg::~GpsAccelMsg()
{

}
bool GpsAccelMsg::getData( AccelVector *data)
{
	*data = myData;
	 return true;
}
bool GpsAccelMsg::setData( AccelVector *data)
{
	myData = *data;
	 return true;
}
