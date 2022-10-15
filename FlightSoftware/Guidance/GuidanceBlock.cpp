#include "GuidanceBlock.h"

#include "XmlUtils.h"
GuidanceBlock::GuidanceBlock( std::string bName ) : Block( bName , 10 , 10 ) 
{
	registerMessage(DroneMsgTypes::EkfStateMsgId);
	registerMessage(DroneMsgTypes::StabilityMsgId);
	registerMessage(DroneMsgTypes::RtbMsgId);
	registerMessage(DroneMsgTypes::LandingMsgId);
	registerMessage(DroneMsgTypes::LiftoffMsgId);
	registerMessage(DroneMsgTypes::WaypointMsgId);
	registerMessage(DroneMsgTypes::IdleMotorMsgId);

	
	maxDt = 0 ;
	PidGain H, V;
	double downsample;
	XmlUtils::GetGuidanceGains("Drone.xml",H, V, downsample);

	myGuidance_.setGains(H, H, V);
	myGuidance_.setDownsample(downsample);

}

GuidanceBlock::~GuidanceBlock() 
{


}

void GuidanceBlock::update()
{

	time_t tTime;
	double dt;
	time(&tTime);
	dt = difftime( tTime , lastTime );
	maxDt = ( dt > maxDt ) ? dt : maxDt ;
	lastTime = tTime;
	unsigned int a;
	unsigned int header;

	
	while( waitingMessages() )
	{
	    header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::EkfStateMsgId:
			rcvMessage( &myEkfStateMsg_ );
			myGuidance_.setInput( &myEkfStateMsg_.myData ) ;
			//std::cout<<"\nGUIDE GET";
			break;
		case DroneMsgTypes::StabilityMsgId:
			rcvMessage(&myStabilityMsg_);
			myGuidance_.setInput(&myStabilityMsg_.myData);
			std::cout << "Guide Stability" << std::endl;
			break;
		case DroneMsgTypes::LiftoffMsgId:
			rcvMessage(&myLiftoffMsg_);
			myGuidance_.setInput(&myLiftoffMsg_.myData);
			std::cout << "Guide liftoff" << std::endl;
			break;
		case DroneMsgTypes::LandingMsgId:
			rcvMessage(&myLandingMsg_);
			myGuidance_.setInput(&myLandingMsg_.myData);
			std::cout << "Guide land" << std::endl;
			break;
		case DroneMsgTypes::RtbMsgId:
			rcvMessage(&myRtbMsg_);
			myGuidance_.setInput(&myRtbMsg_.myData);
			std::cout << "Guide rtb" << std::endl;
			break;
		case DroneMsgTypes::WaypointMsgId:
			rcvMessage(&myyWaypointMsg_);
			myGuidance_.setInput(&myyWaypointMsg_.myData);
			std::cout << "Guide Waypoint" << std::endl;
			break;
		case DroneMsgTypes::IdleMotorMsgId:
			rcvMessage(&myIdleMsg_);
			myGuidance_.setInput(&myIdleMsg_.myData);
			std::cout << "Guide Idle" << std::endl;
			break;
		default:
			std::cout<<"Bad Message Id [Guide]\n";
			break;
		}
	}

	
	CheckSend();

}


void GuidanceBlock::CheckSend()
{

	if( myGuidance_.getOutput( &myGuideMsg_.myData ) )
	{
		sendMessage( &myGuideMsg_ );
	}
	if (myGuidance_.getOutput(&myGuideReportMsg_.myData))
	{
		sendMessage(&myGuideReportMsg_);
		std::cout << "Guide Report" << std::endl;
	}

}