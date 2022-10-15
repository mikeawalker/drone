#ifndef LandingMsg_H
#define LandingMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class LandingMsg : public Message 
{
public: 
	LandingMsg();
	 ~LandingMsg();
	bool getData(LandingData *data);
	bool setData(LandingData *data);
	LandingData myData;
private:
protected:
};
#endif