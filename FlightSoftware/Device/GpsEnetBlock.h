#ifndef GPSENETBLOCK_H
#define GPSENETBLOCK_H


#include <string>

#include "Block.h"
#include "UDP_Device.h"
#include "GpsAccelMsg.h"
#include "GpsPvtMsg.h"

#include <queue>

class GpsEnetBlock : public Block
{

public:
	GpsEnetBlock(std::string bName , unsigned int portNum );
	~GpsEnetBlock();
	void update();

private:
	void ReCalcAccel();
	UDP_Device updDevice_;
	GpsPvtMsg gpsMsg_;
	std::deque<double> xQueue;
	std::deque<double> yQueue;
	std::deque<double> zQueue;
	std::deque<double> tQueue;

	GpsAccelMsg gpsAccelMsg_;
	int k;
protected:

};



#endif