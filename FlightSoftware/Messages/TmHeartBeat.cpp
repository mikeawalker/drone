#include "TmHeartBeat.h"
TmHeartBeat::TmHeartBeat() : Message( sizeof( BeatTime ) )
{
	myHeader.dataSize = sizeof(BeatTime);
	myHeader.messageId = DroneMsgTypes::TmHeartBeatId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
TmHeartBeat::~TmHeartBeat()
{

}
bool TmHeartBeat::getData(BeatTime *data)
{
	*data = myData;
	 return true;
}
bool TmHeartBeat::setData(BeatTime *data)
{
	myData = *data;
	 return true;
}
