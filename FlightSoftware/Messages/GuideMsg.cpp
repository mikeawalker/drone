#include "GuideMsg.h"
GuideMsg::GuideMsg() : Message( sizeof( GuidanceCmd ) )
{
	myHeader.dataSize = sizeof(GuidanceCmd);
	myHeader.messageId = DroneMsgTypes::GuideMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
GuideMsg::~GuideMsg()
{

}
bool GuideMsg::getData(GuidanceCmd *data)
{
	*data = myData;
	 return true;
}
bool GuideMsg::setData(GuidanceCmd *data)
{
	myData = *data;
	 return true;
}
