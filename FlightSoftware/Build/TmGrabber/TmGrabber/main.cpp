#include <iostream>
#include <fstream>

#include "UDP_Device.h"
#include "Message.h"
#include "MessageTypes.h"
#include "DroneMsgTypes.h"
#include "ImuMsg.h"
#include "MagMsg.h"
#include "EkfStateMsg.h"
#include "GpsPvtMsg.h"
#include <string.h>

int main(void)
{
	unsigned int header;
	UDP_Device myUdp;
	char buff[300];
	Message *tmp;
	unsigned int portnum = 3500;
	ImuMsg* imuMsg_;
	GpsPvtMsg *gpsMsg;
	MagMsg* magMsg_;
	FILE *fpMag;
	FILE *fpImu;
	FILE *fpState;
	FILE *fpGps;
	fpImu = fopen("ImuData.dat","w");
	//fprintf(fpImu, "ImuTime , AX, AY, AZ, WX , WY , WZ\n");
	fpMag = fopen("MagData.dat", "w");
	//fprintf(fpMag, "MagTime , MagX1 , MagY1 , MagZ1 , MagX2 , MagY2 , MagZ2\n");
	fpState = fopen("StateData.dat", "w");
	//fprintf(fpState, "StateTime, X , Y , Z , Vx , Vy , Vz , q0 , q1 , q2 , q3 , ab1 ,ab2 , ab3 ,wb1,wb2,wb3\n");
	fpGps = fopen("GpsData.dat", "w");
	fclose(fpMag);
	fclose(fpImu);
	fclose(fpState);
	fclose(fpGps);
	EkfStateMsg* stateMsg_;
	int count = 0;
	myUdp.Open(portnum);
	bool run = true;
	while (run)
	{
		myUdp.Recv(buff, 300);
		tmp = (Message*)buff;
		header = tmp->myHeader.messageId;
		switch (header)
		{
		case DroneMsgTypes::ImuMsgId:
			imuMsg_ = (ImuMsg*) buff;
			fpImu = fopen("ImuData.dat", "a");
			fprintf(fpImu,"%f %f %f %f %f %f %f \n", imuMsg_->myData.time, imuMsg_->myData.a_b1, imuMsg_->myData.a_b2, imuMsg_->myData.a_b3
				, imuMsg_->myData.w_b1, imuMsg_->myData.w_b2, imuMsg_->myData.w_b3);
			printf("Grab: imu %d \n", count++);
			fclose(fpImu);

			break;
		case DroneMsgTypes::MagMsgId:
			magMsg_ = (MagMsg*)buff;

			fpMag = fopen("MagData.dat", "a");
			fprintf(fpMag, "%f %f %f %f\n", magMsg_->myData.time, magMsg_->myData.mag1_x, magMsg_->myData.mag1_y, magMsg_->myData.mag1_z);
			//printf("Grab: Mag \n");
			fclose(fpMag);
			break;
		case DroneMsgTypes::EkfStateMsgId:
			stateMsg_ = (EkfStateMsg*)buff;
			FullState *myState;
			myState = (FullState*)&buff[sizeof(stateMsg_->myHeader)+8];
			//myState = &stateMsg_->myData;//For WinDrone only
			fpState = fopen("StateData.dat", "a");
			fprintf(fpState,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", myState->time
				, myState->pos[0], myState->pos[1], myState->pos[2]
				, myState->vel[0], myState->vel[1], myState->vel[2]
				, myState->q[0], myState->q[1], myState->q[2], myState->q[3]
				, myState->accel[0], myState->accel[1], myState->accel[2]
				, myState->omega[0], myState->omega[1], myState->omega[2]);
			fclose(fpState);
		//	printf("Grab: Ekf %d %d %d \n", sizeof(EkfStateMsg), sizeof(stateMsg_->myHeader), sizeof(stateMsg_->myData));
			break;
		case DroneMsgTypes::GpsPvtMsgId:
			gpsMsg = (GpsPvtMsg*)buff;

			fpGps = fopen("GpsData.dat", "a");
			fprintf(fpMag, "%f %f %f %f\n", gpsMsg->myData.time, gpsMsg->myData.X_ECEF, gpsMsg->myData.Y_ECEF, gpsMsg->myData.Z_ECEF);
			//printf("Grab: Mag \n");
			fclose(fpGps);
			break;
		default:
			std::cout << "Bad Message Id [TM]\n";
			break;
		}





	}
	fclose(fpMag);
	fclose(fpImu);
	fclose(fpState);
	return(0);
}