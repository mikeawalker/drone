#ifndef ETHERNETCONTROL_H
#define ETHERNETCONTROL_H

#include "Block.h"

#include "UDP_Device.h"
// In Msg
#include "GpsPvtMsg.h"
#include "MagMsg.h"
#include "ImuMsg.h"

class EthernetControl : public Block
{

public:
	EthernetControl(unsigned int portNum);
	~EthernetControl();
	void update();
private:
	UDP_Device udpDevice_;
	GpsPvtMsg myGpsMsg_;
	MagMsg myMagMsg_;
	ImuMsg myImuMsg_;
protected:

};
#endif