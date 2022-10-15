#include "Interrupt_Interface.h"

InterruptInterface::InterruptInterface(std::string bName) : Block(bName, 10, 10) ,
myInterrupt_("MyInterrupt", &magInterruptMsg_, 0)
{
	myInterrupt_.start(10);
}

InterruptInterface::~InterruptInterface()
{
	myInterrupt_.stop = true;
}


void InterruptInterface::update()
{
//	myInterrupt_
}
