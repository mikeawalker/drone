#include "EnetTmBlock.h"


EnetTmBlock::EnetTmBlock( std::string bName  , unsigned int portNum)
							: Block( bName , 10 , 10 ) 
{
	
	registerMessage(DroneMsgTypes::ImuMsgId);
	registerMessage(DroneMsgTypes::MagMsgId);
	registerMessage(DroneMsgTypes::EkfStateMsgId);

	registerMessage(DroneMsgTypes::GpsPvtMsgId);
	std::string ip = "192.168.1.114";
	udpDevice_.Open(ip,portNum);
	firstUpdate_ = true;

}

EnetTmBlock::~EnetTmBlock() 
{


}



void EnetTmBlock::update()
{
	unsigned int header;
	

//	printf("ENET!\n");
	while( waitingMessages() )
	{
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::ImuMsgId:
			rcvMessage( &imuMsg_ );
			udpDevice_.Send( &imuMsg_ , sizeof(imuMsg_) ); 
		//	printf("TMSEND: imu \n");
			break;
		case DroneMsgTypes::MagMsgId:
			rcvMessage( &magMsg_ );
			udpDevice_.Send( &magMsg_ , sizeof(magMsg_) );
		//	printf("TMSEND: mag \n");
			break;
		case DroneMsgTypes::EkfStateMsgId:
			rcvMessage( &stateMsg_ );
			udpDevice_.Send( &stateMsg_ , sizeof(stateMsg_) );
		//	printf("TMSEND: %d EKF\n",sizeof(stateMsg_) );
			break;
		case DroneMsgTypes::GpsPvtMsgId:
			rcvMessage(&gpsMsg_);
			udpDevice_.Send(&gpsMsg_, sizeof(gpsMsg_));
			break;
		default:
			std::cout<<"Bad Message Id [TM]\n";
			break;
		}
	}
//printf("XX\n");
}
