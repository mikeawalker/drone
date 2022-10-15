#ifndef MSG_A
#define MSG_A

#include "Message.h"
#include "TestTypes.h"

class MsgA : public Message
{
public:
	MsgA();
	~MsgA();
	bool getData( TestTypes::TypeA *data );
	bool setData( TestTypes::TypeA *data );
	TestTypes::TypeA myData;
private:
protected:

};


#endif