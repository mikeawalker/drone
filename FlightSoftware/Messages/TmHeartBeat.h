#ifndef TmHeartBeat_H
#define TmHeartBeat_H
#include "Message.h"
#include "DroneMsgTypes.h"


 class TmHeartBeat : public Message 
{
public: 
	TmHeartBeat();
	 ~TmHeartBeat();
	bool getData(BeatTime *data);
	bool setData(BeatTime *data);
	BeatTime myData;
private:
protected:
};
#endif