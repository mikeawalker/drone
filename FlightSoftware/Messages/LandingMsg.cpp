#include "LandingMsg.h"
LandingMsg::LandingMsg() : Message( sizeof( LandingData ) )
{
	myHeader.dataSize = sizeof(LandingData);
	myHeader.messageId = DroneMsgTypes::LandingMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
LandingMsg::~LandingMsg()
{

}
bool LandingMsg::getData(LandingData *data)
{
	*data = myData;
	 return true;
}
bool LandingMsg::setData(LandingData *data)
{
	myData = *data;
	 return true;
}
