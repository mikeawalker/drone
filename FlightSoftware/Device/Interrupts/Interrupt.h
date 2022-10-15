#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "Message.h"
#include "Block.h"
#include "MyTime.h"


#include "GPIO_Device.h"
#ifdef LINUX_DEVICE
#include "poll.h"
//#include "priority.h"
#endif
class Interrupt : public Block
{
public:
	Interrupt(std::string intName, Message *msg, std::string gpioPin);
	~Interrupt();
	void mrun();
	void doPoll();
	void doTimePoll();
	void update() {};
	void setTimeout(int to){ timeout = to; };
private:
	Message *msgPtr;

	void gpioInit();
	bool sendMsg_;
	int fd;
	GPIO_Device myGpio;
#ifdef LINUX_DEVICE	
	
	struct pollfd polls;
#endif
	int rc;
	char buff[64];
	static const unsigned int INTERRUPT_PRI = 55;
	int timeout;
protected:

};

#endif
