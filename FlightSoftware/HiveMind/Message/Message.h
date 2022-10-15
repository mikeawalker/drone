#ifndef MESSAGE_H
#define MESSAGE_H

#include "MessageTypes.h"

class Message
{

public:
	Message(int dataSize);
	~Message();
	unsigned int getSize();
	MessageTypes::MessageHeader myHeader;
	char *ldata;
private:
	
protected:
	

};


#endif