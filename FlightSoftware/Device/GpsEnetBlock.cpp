#include "GpsEnetBlock.h"

#include "Tools.h"
GpsEnetBlock::GpsEnetBlock( std::string bName  , unsigned int portNum)
							: Block( bName , 10 , 10 ) 
{
	updDevice_.Open(portNum);
	k = 0;
}

GpsEnetBlock::~GpsEnetBlock() 
{


}

void GpsEnetBlock::update()
{
	double data[7]; //x y z ax ay az t

		updDevice_.Recv(data, sizeof(double)*7 );
	

		gpsMsg_.myData.X_ECEF = data[0];
		gpsMsg_.myData.Y_ECEF = data[1];
		gpsMsg_.myData.Z_ECEF = data[2];
		gpsAccelMsg_.myData.ax = data[3];
		gpsAccelMsg_.myData.ay = data[4];
		gpsAccelMsg_.myData.az = data[5];
		gpsMsg_.myData.time = data[6];
		sendMessage(&gpsMsg_);
	
	
		if (k++ > 4)
		{
			sendMessage(&gpsAccelMsg_);
		}

		mtx.unlock();
		

}
