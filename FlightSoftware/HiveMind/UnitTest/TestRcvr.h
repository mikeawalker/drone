#ifndef TEST_RCVR_H
#define TEST_RCVR_H


#include "MsgA.h"
#include "MsgB.h"
#include "TestTypes.h"
#include <iostream>
#include "Block.h"
class TestRcvr : public Block
{

public:
	TestRcvr(std::string blockName);
	~TestRcvr();
	void update();
private:
	MsgA myA;
	MsgB myB;
protected:

};

#endif