#include "GuidanceReportMsg.h"
GuidanceReportMsg::GuidanceReportMsg() : Message( sizeof( GuidanceReport ) )
{
	myHeader.dataSize = sizeof(GuidanceReport);
	myHeader.messageId = DroneMsgTypes::GuidanceReportMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
GuidanceReportMsg::~GuidanceReportMsg()
{

}
bool GuidanceReportMsg::getData(GuidanceReport *data)
{
	*data = myData;
	 return true;
}
bool GuidanceReportMsg::setData(GuidanceReport *data)
{
	myData = *data;
	 return true;
}
