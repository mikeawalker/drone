#ifndef MAGENETBLOCK_H
#define MAGENETBLOCK_H


#include <string>

#include "Block.h"
#include "UDP_Device.h"

#include "MagMsg.h"

class MagEnetBlock : public Block
{

public:
	MagEnetBlock(std::string bName , unsigned int portNum );
	~MagEnetBlock();
	void update();

private:

	UDP_Device updDevice_;;
	MagMsg magMsg_;
	
protected:

};



#endif