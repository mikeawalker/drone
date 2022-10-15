#include "MsgB.h"


MsgB::MsgB() : Message(sizeof(  TestTypes::TypeB ) )
{
	myHeader.dataSize = sizeof( TestTypes::TypeB );
	myHeader.messageId = TestTypes::MSG_B_ID;
	myHeader.endian = MessageTypes::LITTLE_E;
	ldata = (char*)( & myData ) ;
}
MsgB::~MsgB()
{

}
bool MsgB::getData(TestTypes::TypeB *data)
{
	memcpy( &myData , data , sizeof(TestTypes::TypeB ) ) ;
	return true;
}

bool MsgB::setData(TestTypes::TypeB *data)
{
	
	memcpy( &myData , data , sizeof( TestTypes::TypeB ) );
	return true;
}