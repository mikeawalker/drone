#ifndef GuidanceReportMsg_H
#define GuidanceReportMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class GuidanceReportMsg : public Message 
{
public: 
	GuidanceReportMsg();
	 ~GuidanceReportMsg();
	bool getData(GuidanceReport *data);
	bool setData(GuidanceReport *data);
	GuidanceReport myData;
private:
protected:
};
#endif