#include "Timer_30HzMsg.h"
Timer_30HzMsg::Timer_30HzMsg() : Message( sizeof( bool ) )
{
	myHeader.dataSize = sizeof(bool);
	myHeader.messageId = DroneMsgTypes::Timer_30HzMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
Timer_30HzMsg::~Timer_30HzMsg()
{

}
bool Timer_30HzMsg::getData(bool *data)
{
	*data = myData;
	 return true;
}
bool Timer_30HzMsg::setData(bool *data)
{
	myData = *data;
	 return true;
}
