#include "NavBlock.h"

#include "XmlUtils.h"


NavBlock::NavBlock( std::string bName ) :  Block( bName , 50 , 10  )
{

	registerMessage(DroneMsgTypes::GpsPvtMsgId);
	registerMessage(DroneMsgTypes::ImuMsgId);
	registerMessage(DroneMsgTypes::MagMsgId);
	registerMessage(DroneMsgTypes::GpsAccelMsgId);



	DroneNavInfo myDrone;

	myDrone = XmlUtils::GetNavInfo("Drone.xml");


	StateVector initState;
	initState.r << 0,0,0;
	initState.v << 0,0,0;
	initState.q << 0,0,0,1;
	initState.aBias << 0,0,0;
	initState.wBias << 0,0,0;
	
	

	CovData initCov;
	initCov.Covs <<1 ,1 ,1 ,  0,0 ,0 , .1 ,.1 ,.1 , 1, 1 ,1,  1 ,1, 1 ;
	myNavigator_.Initialize();
	myNavigator_.setImuPosition(0.0,0.0,0.0);
	myNavigator_.setInput(&myDrone);
	myNavigator_.setGpsPosition(0,0,0);
	myNavigator_.setImuPosition(0,0,0);
	myNavigator_.setInput( &initState );
	myNavigator_.setInput( &initCov );


}

NavBlock::~NavBlock()
{


}


void NavBlock::update()
{
	unsigned int a;
	unsigned int header;
	time_t tTime;
	int t1; int t2;
	t1 = clock();

	//printf("NAV\n");
	
	while( waitingMessages() )
	{
		//std::cout << "Nav:  " << inQueue->get_num_msg() << std::endl;
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::GpsPvtMsgId:
			//printf("NAV PVT\n");
			rcvMessage( &myGpsMsg_ );
			myNavigator_.setInput( &myGpsMsg_.myData ) ;
			break;
		case DroneMsgTypes::ImuMsgId:
			//printf("NAV IMU\n");
			rcvMessage( &myImuMsg_ );
			myNavigator_.setInput( &myImuMsg_.myData ) ;
			
			break;
		case DroneMsgTypes::MagMsgId:
			//printf("NAV MAG\n");
			rcvMessage( &myMagMsg_ );
			myNavigator_.setInput( &myMagMsg_.myData) ;
			break;
		//add a ekf init message?
		case DroneMsgTypes::GpsAccelMsgId:
			//printf("NAV Accel\n");
			rcvMessage(&gpsAccelMsg_);
			myNavigator_.setInput(&gpsAccelMsg_.myData);
			break;
		default:
			std::cout<<"Bad Message Id [Nav]:"<<header<<" \n";
			break;
		}

		
	}

	
	t2 = clock();
	//std::cout<<"DT: "<<(float)(t2-t1) / CLOCKS_PER_SEC<<std::endl;
	
	CheckSend();
	//printf("NAV EXIT\n");
}


void NavBlock::CheckSend()
{
	if( myNavigator_.getOutput( &(myEkfStateMsg_.myData) ) ) 
	{
		myNavigator_.outputStateData();
		sendMessage( &myEkfStateMsg_ );
	//	printf("EKF Send\n");
	}
	
}
