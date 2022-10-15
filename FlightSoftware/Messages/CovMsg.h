#ifndef CovMsg_H
#define CovMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class CovMsg : public Message 
{
public: 
	CovMsg();
	 ~CovMsg();
	bool getData(CovArray *data);
	bool setData(CovArray *data);
	CovArray myData;
private:
protected:
};
#endif