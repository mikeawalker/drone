#include "MagMsg.h"
MagMsg::MagMsg() : Message( sizeof( MagMeasurement ) )
{
	myHeader.dataSize = sizeof(MagMeasurement);
	myHeader.messageId = DroneMsgTypes::MagMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
MagMsg::~MagMsg()
{

}
bool MagMsg::getData(MagMeasurement *data)
{
	*data = myData;
	 return true;
}
bool MagMsg::setData(MagMeasurement *data)
{
	myData = *data;
	 return true;
}
