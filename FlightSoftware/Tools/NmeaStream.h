#ifndef NMEASTREAM_H
#define NMEASTREAM_H

#include <string>
#include <iostream>
#include "Defines.h"
#include "Structs.h"
#include "Tools.h"

class NmeaStream
{
public:
	NmeaStream();
	~NmeaStream();

	void append(char *buff, int bytes);
	void initialize(int len);
	void parseAll();
	bool getPVT(GpsMeasurement *gps);
	
private:
	std::string nmeaStream;
	std::string currSentence;
	std::string nmeaId;
	std::string element;
	bool NmeaCkSumOk(std::string toCk);
	bool parseFirstNmea();
	void ParseNmeaSentence();
	void grabElement();
	void fillRMC();
	void fillGPGGA();
	// datas

	bool debugOn_;
	bool pvtAvail_;
	float UnpackLatLong(std::string ddmm);

	NmeaRmc nmeaRmc;
	NmeaGpgga nmeaGpgga;

protected:
};


#endif