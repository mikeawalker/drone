#include "ImuMsg.h"
ImuMsg::ImuMsg() : Message( sizeof( ImuMeasurement ) )
{
	myHeader.dataSize = sizeof(ImuMeasurement);
	myHeader.messageId = DroneMsgTypes::ImuMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
ImuMsg::~ImuMsg()
{

}
bool ImuMsg::getData(ImuMeasurement *data)
{
	*data = myData;
	 return true;
}
bool ImuMsg::setData(ImuMeasurement *data)
{
	myData = *data;
	 return true;
}
