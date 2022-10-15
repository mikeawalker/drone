#include "FileTmBlock.h"
#include <ctime>
#include <string>
#include <iostream>
FileTmBlock::FileTmBlock( std::string bName  )
							: Block( bName , 10 , 10 ) 
{
	
//	registerMessage(DroneMsgTypes::ImuMsgId);
//	registerMessage(DroneMsgTypes::MagMsgId);
	registerMessage(DroneMsgTypes::EkfStateMsgId);

	registerMessage(DroneMsgTypes::GpsPvtMsgId);
	std::string gpsFileName;
	std::string ekfFileName;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%H%M%S", timeinfo);
	std::string time1(buffer);

	ekfFileName = "./data/ekf_" + time1 + ".txt";
	gpsFileName = "./data/gps_" + time1  + ".txt";
	gpsFile = fopen(gpsFileName.c_str(), "w");
	ekfFile = fopen(ekfFileName.c_str(), "w");
	firstUpdate_ = true;
	std::cout << "GPS " << gpsFileName << std::endl;
	std::cout << "EKF " << ekfFileName << std::endl;

	std::cout << "FILE Status " << gpsFile << " " << ekfFile << std::endl;
}


FileTmBlock::~FileTmBlock() 
{
	fclose(gpsFile);
	fclose(ekfFile);

}



void FileTmBlock::update()
{
	unsigned int header;
	

	//printf("File!\n");
	while( waitingMessages() )
	{
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::ImuMsgId:
			rcvMessage( &imuMsg_ );
		//	udpDevice_.Send( &imuMsg_ , sizeof(imuMsg_) ); 
		//	printf("TMSEND: imu \n");
			break;
		case DroneMsgTypes::MagMsgId:
			rcvMessage( &magMsg_ );
		//	udpDevice_.Send( &magMsg_ , sizeof(magMsg_) );
		//	printf("TMSEND: mag \n");
			break;
		case DroneMsgTypes::EkfStateMsgId:
			rcvMessage( &stateMsg_ );
		//	printf("A: EKF \n");
			fprintf(ekfFile, "%f %f %f %f %f %f %f %f %f %f %f\n", 
				stateMsg_.myData.time, 
				stateMsg_.myData.pos[0], stateMsg_.myData.pos[1], stateMsg_.myData.pos[2],
				stateMsg_.myData.vel[0], stateMsg_.myData.vel[1], stateMsg_.myData.vel[2] ,
				stateMsg_.myData.q[0], stateMsg_.myData.q[1], stateMsg_.myData.q[2], stateMsg_.myData.q[3]);
		//	printf("TMSEND: %d EKF\n",sizeof(stateMsg_) );
			break;
		case DroneMsgTypes::GpsPvtMsgId:
		//	printf("B GPS \n");
			rcvMessage(&gpsMsg_);
			fprintf(gpsFile, "%f %f %f %f\n", gpsMsg_.myData.time, gpsMsg_.myData.X_ECEF, gpsMsg_.myData.Y_ECEF, gpsMsg_.myData.Z_ECEF);
			break;
		default:
			std::cout<<"Bad Message Id [TM]\n";
			break;
		}
	}
//printf("XX\n");
}
