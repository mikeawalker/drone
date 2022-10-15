#include "Message.h"


Message::Message(int dataSize)
{
	// set to default size;
	myHeader.preamble =  MessageTypes::MSG_PREAMBLE;
	myHeader.extra = MessageTypes::MSG_POSTFIX;
	myHeader.dataSize = MessageTypes::DEFAULT_DATA_SIZE;
	myHeader.messageId = 0x1000;
	myHeader.endian = MessageTypes::LITTLE_E;
	strcpy(myHeader.sender , "Unset");
	
}


Message::~Message()
{
	//delete myData;
}
unsigned int Message::getSize()
{
	return ( myHeader.dataSize  );
}