#include "ApBlock.h"

#include "XmlUtils.h"
ApBlock::ApBlock( std::string bName ) : Block( bName , 10 , 10 ) 
{
	registerMessage(DroneMsgTypes::GuideMsgId);
    registerMessage(DroneMsgTypes::EkfStateMsgId);


	myAutopilot_.Reset();
	DroneProperties myDrone;
	myDrone.J_motor = 0.01;
	myDrone.mass = 1;
	myDrone.Inertia << 0.5,0,0 ,0 ,1.5 ,0 , 0 ,0 ,2.0;
	
	myAutopilot_.setInput( &myDrone );

	ApGain pitch;
	ApGain roll;
	ApGain yaw;
	double spinUpDelta;
	double spinUp0;
	XmlUtils::GetApGains("Drone.xml", roll, pitch, yaw);
	XmlUtils::GetSpinUp("Drone.xml",  spinUpDelta , spinUp0);
	myAutopilot_.setGains(roll, pitch, yaw);
	myAutopilot_.setSpinUp( spinUpDelta , spinUp0);
}

ApBlock::~ApBlock() 
{


}

void ApBlock::update()
{

	unsigned int a;
	unsigned int header;
	
	while( waitingMessages() )
	{
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::GuideMsgId:
			rcvMessage( &guideMsg_ );
			myAutopilot_.setInput( &guideMsg_.myData ) ;
			break;
		case DroneMsgTypes::EkfStateMsgId:
			rcvMessage( &ekfStateMsg_);
			myAutopilot_.setInput( &ekfStateMsg_.myData ) ;
			//std::cout<<"\nAP GET";
			break;
		default:
			std::cout<<"Bad Message Id [Guide]\n";
			break;
		}
	}

	
	CheckSend();

}


void ApBlock::CheckSend()
{

	if( myAutopilot_.getOutput( &bladeCmdMsg_.myData ) )
	{
		sendMessage( &bladeCmdMsg_ );
	}
	if (myAutopilot_.getOutput(&apReportMsg_.myData))
	{
		sendMessage(&apReportMsg_);
	}
}