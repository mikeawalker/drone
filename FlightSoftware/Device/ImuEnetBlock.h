#ifndef IMUENETBLOCK_H
#define IMUENETBLOCK_H


#include <string>

#include "Block.h"
#include "UDP_Device.h"

#include "ImuMsg.h"

class ImuEnetBlock : public Block
{

public:
	ImuEnetBlock(std::string bName , unsigned int portNum );
	~ImuEnetBlock();
	void update();


private:

	UDP_Device updDevice_;;
	ImuMsg imuMsg_;
	
protected:

};



#endif