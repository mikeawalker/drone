#include "TimerSetupMsg.h"
TimerSetupMsg::TimerSetupMsg() : Message( sizeof( TimerSetup ) )
{
	myHeader.dataSize = sizeof(TimerSetup);
	myHeader.messageId = DroneMsgTypes::TimerSetupMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
TimerSetupMsg::~TimerSetupMsg()
{

}
bool TimerSetupMsg::getData(TimerSetup *data)
{
	*data = myData;
	 return true;
}
bool TimerSetupMsg::setData(TimerSetup *data)
{
	myData = *data;
	 return true;
}
