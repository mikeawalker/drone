#ifndef MSG_B
#define MSG_B

#include "Message.h"
#include "TestTypes.h"

class MsgB : public Message
{
public:
	MsgB();
	~MsgB();
	bool getData( TestTypes::TypeB *data );
	bool setData( TestTypes::TypeB *data );
	TestTypes::TypeB myData;
private:
protected:

};


#endif