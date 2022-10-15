#ifndef EkfStateMsg_H
#define EkfStateMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class EkfStateMsg : public Message 
{
public: 
	EkfStateMsg();
	 ~EkfStateMsg();
	bool getData(FullState *data);
	bool setData(FullState *data);
	FullState myData;
private:
protected:
};
#endif