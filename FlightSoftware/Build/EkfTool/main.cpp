#include <iostream>
#include "includes.h"
#include "Navigator.h"
#include <time.h>
int main(void)
{

	std::cout<<"PANDA"<<std::endl;
	FILE *inputFile;
	ImuMeasurement myImu;
	GpsMeasurement myGps;
	MagMeasurement myMag;
	Navigator myNavigator;
	StateVector outState;
	clock_t t1, t2;
	inputFile = fopen("C:/Workspace/Drone/EKF/Simulation/Scripts/KalmanInputs.dat","rb");
	if( inputFile == NULL ) 
	{
		fputs ("File error",stderr); 
		std::cout<<std::endl<<strerror(errno)<<std::endl;
		exit (1);
	}

	DroneNavInfo myDrone;

	myDrone.accelVar << .1 , .1 , .1;
	myDrone.gyroVar << .1 , .1 , .1;
	myDrone.gpsPosVar << 1,1,1;
	myDrone.gpsVelVar << .1 , .1 , .1;
	myDrone.magVar << .1 , .1 , .1;

	StateVector initState;
	initState.r << 0,0,3;
	initState.v << 0,0,0;
	initState.q << 0,0,0,1;
	initState.aBias << 0,0,0;
	initState.wBias << 0,0,0;
	
	

	CovData initCov;
	initCov.Covs <<1 ,1 ,1 ,  .1 ,.1 ,.1 , 1 ,1 ,1 , 10, 10 ,10,  0.5 ,0.5, 0.5  ;
	
	bool isImu;
	bool isGps;
	bool isMag;
	unsigned int type;
	myNavigator.Initialize();
	myNavigator.setImuPosition(0.0,0.0,0.0);
	myNavigator.setInput(&myDrone);
	myNavigator.setGpsPosition(0,1,0);
	myNavigator.setImuPosition(0,0,0);
	myNavigator.setInput( &initState );
	myNavigator.setInput( &initCov );
	
	while( !feof(inputFile) )
	{
		
		
		fread( &type , sizeof(int) , 1 , inputFile );
		isImu = (type == 1);
		isGps = (type == 2);
		isMag = (type == 3);
		t1 = clock();
		if( isImu )
		{
			fread( &myImu , sizeof( ImuMeasurement) , 1, inputFile );
			myNavigator.setInput( &myImu ) ;
		}
		else if(isMag)
		{
			fread( &myMag , sizeof( MagMeasurement) , 1, inputFile );
			myNavigator.setInput( &myMag );
		}
		else if(isGps)
		{
			fread( &myGps , sizeof( GpsMeasurement) , 1, inputFile );
			myNavigator.setInput( &myGps ) ;
		}
		else
		{
			std::cout<<"WTF MATE"<<std::endl;
		}
		t2 = clock();
		myNavigator.outputDebugData();
		myNavigator.outputStateData( );
		std::cout<<((float)( t2-t1  ) / CLOCKS_PER_SEC)<<std::endl;
	}
	fclose(inputFile);

	return 0;
}