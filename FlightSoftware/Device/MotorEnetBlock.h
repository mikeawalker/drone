#ifndef MOTORENETBLOCK_H
#define MOTORENETBLOCK_H


#include <string>

#include "Block.h"
#include "UDP_Device.h"

#include "BladeCmdMsg.h"

class MotorEnetBlock : public Block
{

public:
	MotorEnetBlock(std::string bName , unsigned int portNum );
	~MotorEnetBlock();
	void update();
	void ULock();
private:
	bool firstUpdate_;
	UDP_Device updDevice_;;
	BladeCmdMsg bladeMsg_;
	
protected:

};



#endif