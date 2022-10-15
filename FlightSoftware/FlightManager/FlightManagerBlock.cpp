#include "FlightManagerBlock.h"


#include "XmlUtils.h"
FlightManagerBlock::FlightManagerBlock(std::string bName) : Block( bName , 10 , 10 )
{

	registerMessage(DroneMsgTypes::EkfStateMsgId);
	registerMessage(DroneMsgTypes::UserCmdMsgId);
	registerMessage(DroneMsgTypes::GuidanceReportMsgId);
	registerMessage(DroneMsgTypes::AutopilotReportMsgId);
	FlightCmds cmds;
	cmds = XmlUtils::GetFlightCmds("Drone.xml");

	myFlightManager_.setCommands(cmds);

}

FlightManagerBlock::~FlightManagerBlock()
{


}


void FlightManagerBlock::update()
{
	unsigned int a;
	unsigned int header;
	
	while( waitingMessages() )
	{
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::EkfStateMsgId:
			rcvMessage( &myEkfStateMsg_ );
			myFlightManager_.setInput( &myEkfStateMsg_.myData ) ;
			break;
		case DroneMsgTypes::UserCmdMsgId:
			rcvMessage(&myUserCmdMsg_);
			myFlightManager_.setInput(&myUserCmdMsg_.myData);
		case DroneMsgTypes::GuidanceReportMsgId:
			rcvMessage(&myGuideanceReportMsg_);
			myFlightManager_.setInput(&myGuideanceReportMsg_.myData);
			break;
		case DroneMsgTypes::AutopilotReportMsgId:
			rcvMessage(&myApReportMsg_);
			myFlightManager_.setInput(&myApReportMsg_.myData);
			break;
		default:
			std::cout<<"Bad Message Id [Nav]\n";
			break;
		}

		
	}
	myFlightManager_.runStateMachine();
	CheckSend();
}


void FlightManagerBlock::CheckSend()
{
	if( myFlightManager_.getOutput(&myStabilityMsg_.myData) ) 
	{
		sendMessage( &myStabilityMsg_);
	}
	if (myFlightManager_.getOutput(&myLiftoffMsg_.myData))
	{
		sendMessage(&myLiftoffMsg_);
	}
	if (myFlightManager_.getOutput(&myRtbMsg_.myData))
	{
		sendMessage(&myRtbMsg_);
	}
	if (myFlightManager_.getOutput(&myLandingMsg_.myData))
	{
		sendMessage(&myLandingMsg_);
	}
	if (myFlightManager_.getOutput(&myWaypointMsg_.myData))
	{
		sendMessage(&myWaypointMsg_);
	}
	if (myFlightManager_.getOutput(&myIdleMsg_.myData))
	{
		sendMessage(&myIdleMsg_);
	}

}