#ifndef LiftoffMsg_H
#define LiftoffMsg_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class LiftoffMsg : public Message 
{
public: 
	LiftoffMsg();
	 ~LiftoffMsg();
	bool getData( LiftoffData *data);
	bool setData( LiftoffData *data);
	 LiftoffData myData;
private:
protected:
};
#endif