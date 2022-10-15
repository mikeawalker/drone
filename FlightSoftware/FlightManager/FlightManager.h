#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H


#include "Structs.h"

class FlightManager
{
public:
	FlightManager();
	~FlightManager();


	void setInput(FullState *state);
	void setInput(UserCmd *data);
	void setInput(GuidanceReport *data);
	void setInput(AutopilotReport *data);
	bool getOutput(StabilityCmd *stabilize);
	bool getOutput(LandingData *data);
	bool getOutput(LiftoffData *data);
	bool getOutput(ReturnToBase *data);
	bool getOutput(WaypointLocation *data);
	bool getOutput(IdleCmd  *data);

	void runStateMachine();

	void setCommands(FlightCmds cmd);
private:


	void handleHold();

	StateTypes::FlightState currentState_;
	StateTypes::FlightState lastState_;

	void runStartup();
	void runGround();
	void runLiftoff();
	void runPreprogWaypoint();
	void runStabilize();
	
	void runRtb();
	void runLanding();
	void runOverRide();

	FlightCmds flightCmds_;

	bool landingComplete_;
	bool liftoffComplete_;
	bool stabilityFixed_;
	bool startupComplete_;
	bool unstableAttitude_;
	bool baseReached_;
	bool readyToFly_;
	bool waypointsDone_;
	bool landCmd;
	bool rtbCmd;

	bool sendLanding_;
	bool sendTakeoff_;
	bool sendStability_;
	bool sendRtb_;
	bool sendWaypoint_;
	bool sendIdle_;


	bool overridePending_;
	bool stabilityCmdPending_;
	

	StabilityCmd overrideCmd;
	FullState myState;

	std::string easyTraj;
protected:

};

#endif