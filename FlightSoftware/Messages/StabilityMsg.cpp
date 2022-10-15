#include "StabilityMsg.h"
StabilityMsg::StabilityMsg() : Message( sizeof( StabilityCmd ) )
{
	myHeader.dataSize = sizeof(StabilityCmd);
	myHeader.messageId = DroneMsgTypes::StabilityMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
StabilityMsg::~StabilityMsg()
{

}
bool StabilityMsg::getData(StabilityCmd *data)
{
	*data = myData;
	 return true;
}
bool StabilityMsg::setData(StabilityCmd *data)
{
	myData = *data;
	 return true;
}
