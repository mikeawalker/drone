#include "UserCmdMsg.h"
UserCmdMsg::UserCmdMsg() : Message( sizeof( UserCmd ) )
{
	myHeader.dataSize = sizeof(UserCmd);
	myHeader.messageId = DroneMsgTypes::UserCmdMsgId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
UserCmdMsg::~UserCmdMsg()
{

}
bool UserCmdMsg::getData(UserCmd *data)
{
	*data = myData;
	 return true;
}
bool UserCmdMsg::setData(UserCmd *data)
{
	myData = *data;
	 return true;
}
