#include "Timer_1000HzMsg.h"
Timer_1000HzMsg::Timer_1000HzMsg() : Message( sizeof( bool ) )
{
	myHeader.dataSize = sizeof(bool);
	myHeader.messageId = DroneMsgTypes::Timer_1000HzMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
Timer_1000HzMsg::~Timer_1000HzMsg()
{

}
bool Timer_1000HzMsg::getData(bool *data)
{
	*data = myData;
	 return true;
}
bool Timer_1000HzMsg::setData(bool *data)
{
	myData = *data;
	 return true;
}
