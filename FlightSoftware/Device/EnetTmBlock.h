#ifndef ENETTMBLOCK_H
#define ENETTMBLOCK_H


#include <string>

#include "Block.h"
#include "UDP_Device.h"

#include "ImuMsg.h"
#include "MagMsg.h"
#include "EkfStateMsg.h"
#include "GpsPvtMsg.h"
class EnetTmBlock : public Block
{

public:
	EnetTmBlock(std::string bName , unsigned int portNum );
	~EnetTmBlock();
	void update();
	void ULock();
private:
	bool firstUpdate_;
	UDP_Device udpDevice_;
	MagMsg magMsg_;
	ImuMsg imuMsg_;
	EkfStateMsg stateMsg_;
	GpsPvtMsg gpsMsg_;
protected:

};



#endif