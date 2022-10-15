#include "EkfStateMsg.h"
EkfStateMsg::EkfStateMsg() : Message( sizeof( FullState ) )
{
	myHeader.dataSize = sizeof(FullState);
	myHeader.messageId = DroneMsgTypes::EkfStateMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
EkfStateMsg::~EkfStateMsg()
{

}
bool EkfStateMsg::getData(FullState *data)
{
	*data = myData;
	 return true;
}
bool EkfStateMsg::setData(FullState *data)
{
	myData = *data;
	 return true;
}
