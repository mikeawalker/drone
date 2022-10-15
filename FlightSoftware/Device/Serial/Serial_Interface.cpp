#include "Serial_Interface.h"



Serial_Interface::Serial_Interface(std::string bName ) : Block(bName,10,10) ,
gpsPower_(GPS_POWER_PIN),
myTimer(100, getMutex() )
{
	firstMeasure = true;
	msCtr = 1;

	mySerial_.Open("/dev/ttyAMA0");
	mySerial_.Configure(56700);
	myGpsDevice_.linkSerial( &mySerial_ );
	myGpsDevice_.setupGps();



	myTimer.start(22);
}

Serial_Interface::~Serial_Interface()
{
}

void Serial_Interface::update()
{
	
	myGpsDevice_.readGps();
	CheckSend();
	msCtr++;
	//std::cout<<"GPS Exit"<<std::endl;
}

void Serial_Interface::CheckSend()
{
	boost::posix_time::time_duration timeOut;
	currTime_ = boost::posix_time::microsec_clock::universal_time();
	
	if( firstMeasure )
	{
		firstTime_ = currTime_;
		firstMeasure = false;
		mySerial_.Clear();
	}
	timeOut = currTime_ - firstTime_;
	if( myGpsDevice_.getPvt( &gpsMsg_.myData) )
	{
		gpsMsg_.myData.time = timeOut.total_milliseconds() * 0.001;
		ReCalcAccel();
//		printf("GPS\n");	
		//std::cout << "GPS: " << gpsMsg_.myData.X_ECEF << " "<<gpsMsg_.myData.Y_ECEF <<" "<< gpsMsg_.myData.Z_ECEF << std::endl;
		sendMessage( &gpsMsg_ );
		//printf("GPS PVT\n");		
		if (xQueue.size() == 3)
		{
			
			sendMessage(&gpsAccelMsg_);
		}
	}
	
}


void Serial_Interface::ReCalcAccel()
{
	double xa, ya, za;
	while(xQueue.size() > 3)
	{
		xQueue.pop_front();
		yQueue.pop_front();
		zQueue.pop_front();
		tQueue.pop_front();
	}
	xQueue.push_back(gpsMsg_.myData.X_ECEF);
	yQueue.push_back(gpsMsg_.myData.Y_ECEF);
	zQueue.push_back(gpsMsg_.myData.Z_ECEF);
	tQueue.push_back(gpsMsg_.myData.time);
	if (xQueue.size() == 3)
	{
		gpsAccelMsg_.myData.ax = calcAccel(xQueue[0], xQueue[1], xQueue[2], tQueue[0], tQueue[1], tQueue[2]);
		gpsAccelMsg_.myData.ay = calcAccel(yQueue[0], yQueue[1], yQueue[2], tQueue[0], tQueue[1], tQueue[2]);
		gpsAccelMsg_.myData.az = calcAccel(zQueue[0], zQueue[1], zQueue[2], tQueue[0], tQueue[1], tQueue[2]);
	}
}
