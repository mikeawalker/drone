#ifndef GuideMsg_H
#define GuideMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class GuideMsg : public Message 
{
public: 
	GuideMsg();
	 ~GuideMsg();
	bool getData(GuidanceCmd *data);
	bool setData(GuidanceCmd *data);
	GuidanceCmd myData;
private:
protected:
};
#endif