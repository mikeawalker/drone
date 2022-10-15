#ifndef MagInterrupt_H
#define MagInterrupt_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class MagInterrupt : public Message 
{
public: 
	MagInterrupt();
	 ~MagInterrupt();
	bool getData(bool *data);
	bool setData(bool *data);
	bool myData;
private:
protected:
};
#endif