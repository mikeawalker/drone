#include "RtbMsg.h"
RtbMsg::RtbMsg() : Message( sizeof( ReturnToBase ) )
{
	myHeader.dataSize = sizeof(ReturnToBase);
	myHeader.messageId = DroneMsgTypes::RtbMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
RtbMsg::~RtbMsg()
{

}
bool RtbMsg::getData(ReturnToBase *data)
{
	*data = myData;
	 return true;
}
bool RtbMsg::setData(ReturnToBase *data)
{
	myData = *data;
	 return true;
}
