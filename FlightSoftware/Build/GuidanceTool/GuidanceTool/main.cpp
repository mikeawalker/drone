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
#include <fstream>

#include "Guidance.h"

int main()
{
	

	//UDP_Device mySimLink;
	int portNum;
	double inVal = -1.0;
	double in[7];
	double out[4];
	Guidance  myGuidance;
	FullState state1;
	GuidanceCmd myTraj;
	double debug[5];
	FILE *inputFile;

	portNum = 9090;
	//mySimLink.Initialize(portNum);
	
	myGuidance.LoadTrajectory();

	out[0] = out[1] = out[2] = out[3] = 0;
	//mySimLink.Send( (void*)(&out), sizeof(double)*4 ) ;
	inputFile = fopen("C:/Workspace/Drone/EKF/Simulation/Scripts/GuidanceInputs.dat","rb");
	if( inputFile == NULL ) 
	{
		fputs ("File error",stderr); 
		std::cout<<std::endl<<strerror(errno)<<std::endl;
		exit (1);
	}
	int k =0;
	while( !feof( inputFile)  ) 
	{
	
		k++;
		//mySimLink.Recv( (void*)(&in) , sizeof(double)*6 );
		//
		fread( in , sizeof(double) , 7, inputFile);
		state1.pos <<in[1] , in[2] , in[3];
		state1.vel << in[4] , in[5] , in[6];
		state1.time =in[0];
		myGuidance.setInput(&state1);

		myGuidance.getOutput( &myTraj );
		//
	
		myGuidance.getDebug(&debug[0]);
		
		//std::cout<<"Sending"<<std::endl;
		//mySimLink.Send( (void*)(&out), sizeof(double)*4 ) ;
	}

	//mySimLink.Close();
	fclose(inputFile);
	return 0;
}