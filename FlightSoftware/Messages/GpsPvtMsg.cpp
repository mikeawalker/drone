#include "GpsPvtMsg.h"
GpsPvtMsg::GpsPvtMsg() : Message( sizeof( GpsMeasurement ) )
{
	myHeader.dataSize = sizeof(GpsMeasurement);
	myHeader.messageId = DroneMsgTypes::GpsPvtMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
GpsPvtMsg::~GpsPvtMsg()
{

}
bool GpsPvtMsg::getData(GpsMeasurement *data)
{
	*data = myData;
	 return true;
}
bool GpsPvtMsg::setData(GpsMeasurement *data)
{
	myData = *data;
	 return true;
}
