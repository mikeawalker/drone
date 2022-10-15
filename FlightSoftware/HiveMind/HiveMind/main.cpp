
#include <iostream>
#include "Hive.h"
#include "TestRcvr.h"
#include "TestSender.h"
#include <vector>
#include "windows.h"

int main(void)
{

	Hive myHive;
	TestRcvr myRcvr("Rcv");
	TestSender mySend("Sender");

	myHive.addToHive("Rcv",myRcvr.getMutex());
	myHive.addToHive("Sender",mySend.getMutex());

	
	
	
	mySend.start(3);
	myRcvr.start(4);
	myHive.start(2);

	bool okTogo = true;
	while( okTogo)
	{
		okTogo = !myHive.isDone();
		Sleep(2000);
		
	}
	myHive.join();
	mySend.join();
	myRcvr.join();



	return 0;
}