#include "MagInterrupt.h"
MagInterrupt::MagInterrupt() : Message( sizeof( bool ) )
{
	myHeader.dataSize = sizeof(bool);
	myHeader.messageId = DroneMsgTypes::MagInterruptId;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)(&myData);
}
MagInterrupt::~MagInterrupt()
{

}
bool MagInterrupt::getData(bool *data)
{
	*data = myData;
	 return true;
}
bool MagInterrupt::setData(bool *data)
{
	myData = *data;
	 return true;
}
