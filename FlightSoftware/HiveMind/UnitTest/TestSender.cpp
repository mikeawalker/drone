#include "TestSender.h"



TestSender::TestSender(std::string blockName) : Block( blockName , 10 ,10 ) 
{
	registerMessage(TestTypes::MSG_B_ID);
	firstTime = true;
}



TestSender::~TestSender()
{

}




void TestSender::update()
{
	unsigned int a;
	unsigned int header;
	if( firstTime )
	{
		
		TestTypes::TypeA myDataA;
		myDataA.a = 1;
		myDataA.b = 2;
		myDataA.c = 3.1;
		myDataA.d = 'lol';
		printf("Enter Anything: ");
		std::cin >> a;
		firstTime = false;
		myA.setData( &myDataA );
		sendMessage( &myA );
	}
	while( waitingMessages() )
	{
		header = pullHeader();

		if( header == TestTypes::MSG_B_ID ) 
		{
			rcvMessage( &myB ) ;

		}
		else
		{
			std::cout<<"How did you get here?!?!?!"<<std::endl;
		}

	}
}