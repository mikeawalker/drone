#include "MsgA.h"


MsgA::MsgA() : Message(sizeof(  TestTypes::TypeA ) )
{
	myHeader.dataSize = sizeof( TestTypes::TypeA );
	myHeader.messageId = TestTypes::MSG_A_ID;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)( & myData ) ;
}
MsgA::~MsgA()
{

}
bool MsgA::getData(TestTypes::TypeA *data)
{
	memcpy( &myData , data , sizeof(TestTypes::TypeA ) ) ;
	return true;
}

bool MsgA::setData(TestTypes::TypeA *data)
{
	
	memcpy( &myData , data , sizeof( TestTypes::TypeA ) );
	return true;
}