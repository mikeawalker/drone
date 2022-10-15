#ifndef TEST_SENDER_H
#define TEST_SENDER_H


#include "MsgA.h"
#include "MsgB.h"
#include "TestTypes.h"
#include <iostream>
#include "Block.h"
class TestSender : public Block
{

public:
	TestSender(std::string blockName);
	~TestSender();
	void update();
private:
	bool firstTime;
	MsgA myA;
	MsgB myB;
protected:

};

#endif