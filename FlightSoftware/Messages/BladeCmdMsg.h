#ifndef BladeCmdMsg_H
#define BladeCmdMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class BladeCmdMsg : public Message 
{
public: 
	BladeCmdMsg();
	 ~BladeCmdMsg();
	bool getData(BladeCmd *data);
	bool setData(BladeCmd *data);
	BladeCmd myData;
private:
protected:
};
#endif