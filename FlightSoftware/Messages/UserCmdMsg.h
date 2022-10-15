#ifndef UserCmdMsg_H
#define UserCmdMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class UserCmdMsg : public Message 
{
public: 
	UserCmdMsg();
	 ~UserCmdMsg();
	bool getData(UserCmd *data);
	bool setData(UserCmd *data);
	UserCmd myData;
private:
protected:
};
#endif