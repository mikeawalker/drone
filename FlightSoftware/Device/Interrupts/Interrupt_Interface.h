#ifndef INTERRUPTINTERFACE_H
#define INTERRUPTINTERFACE_H

#include "Interrupt.h"
#include "MagInterrupt.h"
#include "Block.h"
#include "Hive.h"

class InterruptInterface : public Block
{
public:
	InterruptInterface(std::string bName , Hive *hive);
	~InterruptInterface();
	void initialize();
	void update();
	
private:
	Hive *theHive;
	Interrupt myInterrupt_;
	MagInterrupt magInterruptMsg_;
protected:
};

#endif