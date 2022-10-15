#ifndef GROUNDSTREAM_H
#define GROUNDSTREAM_H

#include <string>
#include <iostream>
#include <stdio.h>
#include "Defines.h"
#include "Structs.h"
#include "Tools.h"

#include <fstream>

class GroundStream
{
public:
	GroundStream(bool air);
	~GroundStream();

	void append(char *buff, int bytes);
	void initialize(int len);
	void parseAll();


	// Connections to radio
	void formatMsg(void *data, int size, std::string id);
	std::string getOutMsg() { return outSentence; };
	void setInMsg(std::string in) { inSentence.append(in); };
	//connections to SW

	bool pullGyro(GryoVector *vec);
	bool pullState(FullState &cmd);
	bool pullImu(ImuMeasurement &cmd);
	bool pullHeartBeat(BeatTime &heartBeat);
	bool pullCommand(UserCmd &cmd);
	bool pullGps(GpsMeasurement &gps);
	bool pullMag(MagMeasurement &cmd);
	unsigned char generateCk(std::string in);
private:
	bool parseFirstStream();
	bool checksumOk(std::string toCk);
	void parseInSentence();
	void fillGyro();
	void fillState();
	void pullImu();
	//
	void StateToFile();
	void GyroToFile();
	void ImuToFile();
	void MagToFile();
	void GpsToFile();
	// datas

	bool debugOn_;
	bool fileOut;
	bool heartBeatAvail;
	bool cmdAvail;

	static const std::string a2gPrefix ;
	static const std::string g2aPrefix ;
	static const std::string postfix;

	
	std::string myPrefix;
	std::string inPrefix;
	std::string outSentence;
	std::string inSentence;

	
	GryoVector gyroVec;
	bool gyroReady;
	FullState droneState;
	bool stateAvail;
	ImuMeasurement droneImu;
	MagMeasurement droneMag;
	GpsMeasurement droneGps;
	bool magAvail;
	bool imuAvail;
	bool gpsAvail;
	UserCmd droneCmd;

	//
	FILE *imuFile;
	FILE *magFile;
	FILE *gpsFile;
	FILE *stateFile;

protected:
};


#endif