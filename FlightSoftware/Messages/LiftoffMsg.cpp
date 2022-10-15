#include "LiftoffMsg.h"
LiftoffMsg::LiftoffMsg() : Message( sizeof(  LiftoffData ) )
{
	myHeader.dataSize = sizeof( LiftoffData);
	myHeader.messageId = DroneMsgTypes::LiftoffMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
LiftoffMsg::~LiftoffMsg()
{

}
bool LiftoffMsg::getData( LiftoffData *data)
{
	*data = myData;
	 return true;
}
bool LiftoffMsg::setData( LiftoffData *data)
{
	myData = *data;
	 return true;
}
