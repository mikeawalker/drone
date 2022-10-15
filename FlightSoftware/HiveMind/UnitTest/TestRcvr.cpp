#include "TestRcvr.h"



TestRcvr::TestRcvr(std::string blockName) : Block( blockName , 10 ,10 ) 
{
	registerMessage(TestTypes::MSG_A_ID);

}



TestRcvr::~TestRcvr()
{

}




void TestRcvr::update()
{
	unsigned int a;
	unsigned int header;

	while( waitingMessages() )
	{
		header = pullHeader();

		if( header == TestTypes::MSG_A_ID ) 
		{
			rcvMessage(&myA);
			std::cout<<"RCVR GOT A! \n";
			TestTypes::TypeB bData;
			bData.mathResult = myA.myData.a * myA.myData.c;
			myB.setData( &bData );
			sendMessage( &myB );
		}
		else
		{
			std::cout<<"How did you get here?!?!?!"<<std::endl;
		}

	}
}