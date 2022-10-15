#include "FlightManager.h"
#include <iostream>
#include "Defines.h"


FlightManager::FlightManager()
{
	currentState_ = StateTypes::STARTUP;
	lastState_ = StateTypes::STARTUP;

    landingComplete_ = false;
	liftoffComplete_ = false;
	stabilityFixed_ = false;
	startupComplete_ = false;
	unstableAttitude_ = false;
	baseReached_ = false;
	readyToFly_ = false;
	waypointsDone_ = false;
	overridePending_ = false;
	stabilityCmdPending_ = false;
	sendWaypoint_ = false;

	sendLanding_ = false ;
	sendTakeoff_ = false;
	sendStability_ = false;
	sendRtb_ = false;
	sendIdle_ = false;
	easyTraj = "TrajectoryEasy.dat";

}

FlightManager::~FlightManager()
{

}


void FlightManager::setCommands(FlightCmds cmd)
{
	flightCmds_ = cmd;

}

void FlightManager::runStateMachine()
{
	switch( currentState_ ) 
	{
	case StateTypes::STARTUP:
		runStartup();
		break;
	case StateTypes::GROUND_WAITING:
		runGround();
		break;
	case StateTypes::LIFTOFF:
		runLiftoff();
		break;
	case StateTypes::PREPROG_WAYPOINT:
		runPreprogWaypoint();
		break;
	case StateTypes::STABILIZE:
		runStabilize();
		break;

	case StateTypes::RETURN_TO_BASE:
		runRtb();
		break;
	case StateTypes::LANDING:
		runLanding();
		break;
	case StateTypes::OVERRIDE:
		runOverRide();
		break;
	default:
		//??
		break;
	
	}
	//TODO: Clear Pending cmds?
}

void FlightManager::runStartup()
{

	// startup logic
	
	if( startupComplete_ )
	{
		lastState_ = currentState_;
		currentState_ = StateTypes::GROUND_WAITING;
		sendIdle_ = true;
	}
}

void FlightManager::runGround()
{
	
	
	if( readyToFly_ ) 
	{
		lastState_ = currentState_;
		currentState_ = StateTypes::LIFTOFF;
		readyToFly_ = false;
		sendTakeoff_ = true;

	}
}
void FlightManager::runLiftoff()
{

	if( liftoffComplete_ )
	{
		lastState_ = currentState_;
	    currentState_ = StateTypes::PREPROG_WAYPOINT;
		waypointsDone_ = false;
		sendWaypoint_ = true;
	}
	if( unstableAttitude_ ) 
	{
		lastState_ = currentState_;
		currentState_ = StateTypes::STABILIZE;
	}


}

void FlightManager::runPreprogWaypoint()
{
	if (waypointsDone_)
	{
		lastState_ = currentState_;
		currentState_ = StateTypes::RETURN_TO_BASE;
		waypointsDone_ = false;
	}

}


void FlightManager::runStabilize()
{
	
	if( stabilityFixed_ )
	{
		currentState_ = lastState_;
		lastState_ = StateTypes::STABILIZE;
	}
}


void FlightManager::runRtb()
{

}

void FlightManager::runLanding()
{

	if( landingComplete_ )
	{
		lastState_ = currentState_;
		currentState_ = StateTypes::GROUND_WAITING;
	}	
}

void FlightManager::runOverRide()
{


	if (rtbCmd)
	{
		lastState_ = currentState_;
		currentState_ = StateTypes::RETURN_TO_BASE;
	}
}

void FlightManager::setInput(FullState *state)
{

	myState = *state;
}

void FlightManager::setInput(UserCmd *data)
{
	switch (data->cmd)
	{
	case TAKEOFF:
		std::cout << "TakeOff! " << std::endl;
		readyToFly_ = true;
		break;
	case RTB:
		std::cout << "Return! " << std::endl;
		sendRtb_ = true;
		break;
	case START:
		std::cout << "Start! " << std::endl;
		break;
	case LAND:
		std::cout << "Land! " << std::endl;
		sendLanding_ = true;
		break;
	case OVERRIDE:
		std::cout << "Override! " << std::endl;
		overrideCmd.stabilityPos[0] = myState.pos[0];
		overrideCmd.stabilityPos[1] = myState.pos[1];
		overrideCmd.stabilityPos[2] = myState.pos[2];
		overridePending_ = true;
		break;
	case UP:
		overrideCmd.stabilityPos[2] += GS_DELTA_POS;
		overridePending_ = true;
		break;
	case DOWN:
		overrideCmd.stabilityPos[2] -= GS_DELTA_POS;
		overridePending_ = true;
		break;
	case NORTH:
		overrideCmd.stabilityPos[1] += GS_DELTA_POS;
		overridePending_ = true;
		break;
	case SOUTH:
		overrideCmd.stabilityPos[1] -= GS_DELTA_POS;
		overridePending_ = true;
		break;
	case EAST:
		overrideCmd.stabilityPos[0] += GS_DELTA_POS;
		overridePending_ = true;
		break;
	case WEST:
		overrideCmd.stabilityPos[0] -= GS_DELTA_POS;
		overridePending_ = true;
		break;
	case KILL:
		std::cout << "Kill! " << std::endl;
		break;
	default:
		break;
	}
}

void FlightManager::setInput(GuidanceReport *data)
{
	switch (data->mode)
	{
	case StateTypes::HOLDPOINT:
		handleHold();
		break;
	default:
		break;
	}
}

void FlightManager::setInput(AutopilotReport *data)
{
	if (data->mode == StateTypes::AP_STANDBY)
	{
		startupComplete_ = true;
	}
}

bool FlightManager::getOutput(StabilityCmd *stability)
{
	if (overridePending_)
	{
		*stability = overrideCmd;
		overridePending_ = false;
		return true;
	}
	else if( stabilityCmdPending_ )
	{
		stability->stabilityPos = myState.pos;
		stabilityCmdPending_ = false;
		return true;
	}
	return false;
}

bool FlightManager::getOutput(LandingData *data)
{
	if (sendLanding_)
	{
		lastState_ = currentState_;
		currentState_ = StateTypes::LANDING;
		data->time = myState.time;
		data->duration = myState.pos[2] / flightCmds_.landingAvgVel;//half m/s avg
		sendLanding_ = false;
		return true;
	}
	return false;
}
bool FlightManager::getOutput(LiftoffData *data)
{
	if (sendTakeoff_)
	{
		data->time = myState.time;
		data->hFinal = flightCmds_.liftOffAltitude;
		data->duration = flightCmds_.liftOffDuration;
		sendTakeoff_ = false;
		return true;
	}
	return false;
}

bool FlightManager::getOutput(ReturnToBase *data)
{
	if (sendRtb_)
	{
		data->holdAltitude = myState.pos(2);
		data->time = myState.time;
		data->duration = (myState.pos.norm()) / flightCmds_.returnAvgVel; //( distance / velocity) = time ... do it at 1 mps
		sendRtb_ = false;
		return true;
	}
	return false;
}

bool FlightManager::getOutput(WaypointLocation *data)
{
	if (sendWaypoint_)
	{
		
		strcpy(data->waypointFile, easyTraj.c_str());
		sendWaypoint_ = false;
		return true;
	}
	return false;
}
bool FlightManager::getOutput(IdleCmd  *data)
{
	if (sendIdle_)
	{
		data->accel = flightCmds_.groundIdleAccel;
		sendIdle_ = false;
		return true;
	}
	return false;
}
void FlightManager::handleHold()
{


		switch (currentState_)
		{
		case StateTypes::LIFTOFF:
			liftoffComplete_ = true;
			break;
		case StateTypes::LANDING:
			landingComplete_ = true;
			break;
		case StateTypes::RETURN_TO_BASE:
			baseReached_ = true;
			break;
		case StateTypes::PREPROG_WAYPOINT:
			waypointsDone_ = true;
			break;

		}
}