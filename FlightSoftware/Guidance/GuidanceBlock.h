#ifndef GUIDANCEBLOCK_H
#define GUIDANCEBLOCK_H


#include <string>
#include "Guidance.h"
#include "Block.h"

// In Msg
#include "EkfStateMsg.h"
#include "StabilityMsg.h"
#include "RtbMsg.h"
#include "LiftoffMsg.h"
#include "LandingMsg.h"
#include "WaypointMsg.h"
#include "IdleMotorMsg.h"
// Output Msg
#include "GuideMsg.h"
#include "GuidanceReportMsg.h"
#include <time.h>

class GuidanceBlock : public Block
{

public:
	GuidanceBlock(std::string bName );
	~GuidanceBlock();
	void update();
	void CheckSend();
	double maxDt;

private:
	Guidance myGuidance_;

	GuideMsg myGuideMsg_;
	

	time_t lastTime;
	//input
	StabilityMsg myStabilityMsg_;
	RtbMsg myRtbMsg_;
	LiftoffMsg myLiftoffMsg_;
	LandingMsg myLandingMsg_;
	EkfStateMsg myEkfStateMsg_;
	WaypointMsg myyWaypointMsg_;
	IdleMotorMsg myIdleMsg_;
	//out
	GuidanceReportMsg myGuideReportMsg_;
protected:

};



#endif