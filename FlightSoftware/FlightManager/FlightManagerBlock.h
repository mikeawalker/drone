#ifndef FLIGHTMANAGERBLOCK_H
#define FLIGHTMANAGERBLOCK_H

#include "FlightManager.h"
#include <string>
#include "Block.h"
#include "EkfStateMsg.h"
#include "StabilityMsg.h"
#include "RtbMsg.h"
#include "LiftoffMsg.h"
#include "LandingMsg.h"
#include "UserCmdMsg.h"
#include "GuidanceReportMsg.h"
#include "AutopilotReportMsg.h"
#include "WaypointMsg.h"
#include "IdleMotorMsg.h"

class FlightManagerBlock : public Block
{
public:
	FlightManagerBlock(std::string bname);
	~FlightManagerBlock();
	void CheckSend();
	void update();
private:
	FlightManager myFlightManager_;
	EkfStateMsg myEkfStateMsg_;
	StabilityMsg myStabilityMsg_;
	RtbMsg myRtbMsg_;
	LiftoffMsg myLiftoffMsg_;
	UserCmdMsg myUserCmdMsg_;
	LandingMsg myLandingMsg_;
	GuidanceReportMsg myGuideanceReportMsg_;
	AutopilotReportMsg myApReportMsg_;
	WaypointMsg myWaypointMsg_;
	IdleMotorMsg myIdleMsg_;
protected:
};

#endif