#include "CovMsg.h"
CovMsg::CovMsg() : Message( sizeof( CovArray ) )
{
	myHeader.dataSize = sizeof(CovArray);
	myHeader.messageId = DroneMsgTypes::CovMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
CovMsg::~CovMsg()
{

}
bool CovMsg::getData(CovArray *data)
{
	*data = myData;
	 return true;
}
bool CovMsg::setData(CovArray *data)
{
	myData = *data;
	 return true;
}
