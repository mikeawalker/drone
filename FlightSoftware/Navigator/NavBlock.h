#ifndef NAVBLOCK_H
#define NAVBLOCK_H


#include <string>
#include "Navigator.h"
#include "Block.h"

// In Msg
#include "GpsPvtMsg.h"
#include "MagMsg.h"
#include "ImuMsg.h"
#include "GpsAccelMsg.h"
// Output Msg
#include "EkfStateMsg.h"


#include <ctime>

class NavBlock : public Block
{

public:
	NavBlock(std::string bName );
	~NavBlock();
	void update();
	void CheckSend();
private:
	Navigator myNavigator_;
	
	GpsPvtMsg myGpsMsg_;
	MagMsg myMagMsg_;
	ImuMsg myImuMsg_;
	EkfStateMsg myEkfStateMsg_;
	GpsAccelMsg gpsAccelMsg_;

protected:

};



#endif