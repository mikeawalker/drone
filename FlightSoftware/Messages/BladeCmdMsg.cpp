#include "BladeCmdMsg.h"
BladeCmdMsg::BladeCmdMsg() : Message( sizeof( BladeCmd ) )
{
	myHeader.dataSize = sizeof(BladeCmd);
	myHeader.messageId = DroneMsgTypes::BladeCmdMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
BladeCmdMsg::~BladeCmdMsg()
{

}
bool BladeCmdMsg::getData(BladeCmd *data)
{
	*data = myData;
	 return true;
}
bool BladeCmdMsg::setData(BladeCmd *data)
{
	myData = *data;
	 return true;
}
