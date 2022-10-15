#include "EthernetControl.h"
#include "Block.h"

EthernetControl::EthernetControl(unsigned int portNum) : Block( )
{
	udpDevice_.Open(portNum);
	
	registerMessage(DroneMsgTypes::GpsPvtMsgId);
	registerMessage(DroneMsgTypes::ImuMsgId);
	registerMessage(DroneMsgTypes::MagMsgId);
}


EthernetControl::~EthernetControl()
{

}


void EthernetControl::update()
{
		unsigned int header;
	while( waitingMessages() )
	{
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::GpsPvtMsgId:
			rcvMessage( &myGpsMsg_ );
			udpDevice_.Send(&myGpsMsg_ , sizeof(myGpsMsg_));
						break;
		case DroneMsgTypes::ImuMsgId:
			rcvMessage( &myImuMsg_ );
			udpDevice_.Send(&myImuMsg_ , sizeof(myImuMsg_));
			break;
		case DroneMsgTypes::MagMsgId:
			rcvMessage( &myMagMsg_ );
			udpDevice_.Send(&myMagMsg_ , sizeof(myMagMsg_));
			break;
		//add a ekf init message?
		default:
			std::cout<<"Bad Message Id [Nav]\n";
			break;
		}

		
	}
}


