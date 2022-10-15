#include "Interrupt.h"
#include "MyTime.h"



Interrupt::Interrupt(std::string intName, Message *msg, std::string gpioPin) : Block(intName, 0, 1),
myGpio(gpioPin)
{
	msgPtr = msg;
	stop = false;
	sendMsg_ = false;
	timeout = 10;
}

Interrupt::~Interrupt()
{
}

void Interrupt::mrun()
{
	// Interrupts get high priority
	//(void)piHiPri(INTERRUPT_PRI);	// Only effective if we run as root
	gpioInit();

	while (!stop)
	{
		//printf("Wait?\n");

		// setup poll
		//doTimePoll();
		doPoll();
		// Check send
		if (sendMsg_)
		{
			sendMsg_ = false;
			sendMessage(msgPtr);
		}
	}

}

#ifdef LINUX_DEVICE


void Interrupt::doPoll()
{
	
	int ret;
	// Setup poll structure


	memset((void*)&polls, 0, sizeof(polls));
	polls.fd = fd;
	polls.events = POLLPRI;	// Urgent data!
	rc = poll(&polls, 1, timeout);

	// Do a dummy read to clear the interrupt
	//	A one character read appars to be enough.
		if (rc == 0)
		{
		//	printf("Interrtupt Timeout\n");
		}
		else if (polls.revents & POLLPRI )
		{
			ret = read(polls.fd, &buff[0], 64);
			printf("Interrupt Wakeup %d %s\n" ,ret, buff);
		}
		sendMsg_ = true;
	//	printf("BOOM CITY!\n");


}

void Interrupt::gpioInit()
{
	
	myGpio.enable();
	myGpio.setDirection("in");
	myGpio.setEdge("falling");
	fd = myGpio.getFd();


    
}
void Interrupt::doTimePoll()
{
	//	printf("Int Poll\n");
	MyTime::mSleep(10);
	sendMessage(msgPtr);
}
#else


void Interrupt::gpioInit()
{

}
void Interrupt::doTimePoll()
{
//	printf("Int Poll\n");
	MyTime::mSleep(10);
	sendMessage(msgPtr);
}

void Interrupt::doPoll()
{

}
#endif
