#include "Timer_5HzMsg.h"
Timer_5HzMsg::Timer_5HzMsg() : Message( sizeof( bool ) )
{
	myHeader.dataSize = sizeof(bool);
	myHeader.messageId = DroneMsgTypes::Timer_5HzMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
Timer_5HzMsg::~Timer_5HzMsg()
{

}
bool Timer_5HzMsg::getData(bool *data)
{
	*data = myData;
	 return true;
}
bool Timer_5HzMsg::setData(bool *data)
{
	myData = *data;
	 return true;
}
