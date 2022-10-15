#include "AutopilotReportMsg.h"
AutopilotReportMsg::AutopilotReportMsg() : Message( sizeof( AutopilotReport ) )
{
	myHeader.dataSize = sizeof(AutopilotReport);
	myHeader.messageId = DroneMsgTypes::AutopilotReportMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
AutopilotReportMsg::~AutopilotReportMsg()
{

}
bool AutopilotReportMsg::getData(AutopilotReport *data)
{
	*data = myData;
	 return true;
}
bool AutopilotReportMsg::setData(AutopilotReport *data)
{
	myData = *data;
	 return true;
}
