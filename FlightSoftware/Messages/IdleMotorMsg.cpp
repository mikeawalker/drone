#include "IdleMotorMsg.h"
IdleMotorMsg::IdleMotorMsg() : Message( sizeof(  IdleCmd ) )
{
	myHeader.dataSize = sizeof( IdleCmd);
	myHeader.messageId = DroneMsgTypes::IdleMotorMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
IdleMotorMsg::~IdleMotorMsg()
{

}
bool IdleMotorMsg::getData( IdleCmd *data)
{
	*data = myData;
	 return true;
}
bool IdleMotorMsg::setData( IdleCmd *data)
{
	myData = *data;
	 return true;
}
