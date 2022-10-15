// UDPEchoServer.cpp : Defines the entry point for the console application. 
/* CHANGES FROM UNIX VERSION                                                   */ 
/*                                                                             */ 
/* 1.  Changed header files.                                                   */ 
/* 2.  Added WSAStartUP().                                                     */ 

#include <stdio.h>      /* for printf(), fprintf() */ 
#include <winsock.h>    /* for socket(),... */ 
#include <stdlib.h>     /* for exit() */ 
#include <iostream>
#include <time.h>
#include "UDP_Device.h"
#include "Structs.h"


#include "AutoPilot.h"

int main()
{
	

	
	int portNum;
	double inVal = -1.0;
	double in[20];
	double out[14];
	
	AutoPilot  myAutoPilot;
	//GuidanceCmd myTraj;
	DroneProperties myDrone;
	myDrone.J_motor = 0.05;
	myDrone.mass = 10;
	myDrone.Inertia << 1,0,0 ,0 ,1 ,0 , 0 ,0 ,1;
	FullState myState;
	GuidanceCmd myGuide;
	double qerr[4];
	double werr[3];
	double M[3];
	double bladeRate[4];
	double debug[5];
	myAutoPilot.setInput( &myDrone);
	
	FILE *fIn;
	fIn = fopen("C:/Workspace/Drone/EKF/Simulation/Scripts/AutopilotInputs.dat","rb");

	int k=0;
	
	while( !feof(fIn) ) 
	{
		k++;
		fread( in , sizeof(double) , 20  , fIn );
		myState.q << in[0], in[1], in[2], in[3];
		myState.omega << in[4],in[5],in[6];
		myGuide.accel_cmd << in[14],in[15],in[16];
		myGuide.v_cmd << in[17],in[18],0;
	
		myAutoPilot.setInput(&myState);
		myAutoPilot.setInput(&myGuide);
		
		//myAutoPilot.getCommand(&bladeRate);
	
		std::cout<<"\nk: "<<k<<std::endl;
		
	}

	fclose(fIn);
	return 0;
}