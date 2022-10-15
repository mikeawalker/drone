#ifndef AutopilotReportMsg_H
#define AutopilotReportMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class AutopilotReportMsg : public Message 
{
public: 
	AutopilotReportMsg();
	 ~AutopilotReportMsg();
	bool getData(AutopilotReport *data);
	bool setData(AutopilotReport *data);
	AutopilotReport myData;
private:
protected:
};
#endif