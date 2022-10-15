#include "NmeaStream.h"


NmeaStream::NmeaStream()
{
	debugOn_ = false;
}

NmeaStream::~NmeaStream()
{

}


void NmeaStream::initialize(int len)
{

	nmeaStream.reserve(len);
	currSentence.reserve(100);
	element.reserve(10);
	pvtAvail_ = false;
}


void NmeaStream::append(char *buff, int bytes)
{
	nmeaStream.assign(buff, bytes);
}

void NmeaStream::parseAll()
{
	//std::cout << nmeaStream << std::endl;
	int k = 0;
	while (parseFirstNmea())
	{
		//std::cout << k++ << std::endl;
	}
}

bool NmeaStream::parseFirstNmea()
{
	int dsign1;
	int star;
	std::string sent;

	dsign1 = nmeaStream.find("$");
	star = nmeaStream.find("*", dsign1 + 1);
	if (dsign1 > -1 && star > -1)
	{
		//Both dollar signs exist....full nmea message
		currSentence = nmeaStream.substr(dsign1, star+3-dsign1);
		
		// do checksum
		if (NmeaCkSumOk(currSentence))
		{
			ParseNmeaSentence();
		}
		else
		{
			//bad checksum
			std::cout << "Bad Nmea CkSum\n";
		}

		nmeaStream.erase(dsign1, star+2 - dsign1);
		//std::cout << nmeaStream << std::endl;
	}
	else
	{
		return false; // no full message
	}
	return true;
}




bool NmeaStream::NmeaCkSumOk(std::string toCk)
{
	int len = toCk.length();
	int dSign;
	int starSign;
	int ckSum;
	int ck2 = 0;
	bool strOk; 
	std::string ck;

	dSign = toCk.find("$");
	starSign = toCk.find("*");
	ck = toCk.substr(starSign + 1, 2);
		ckSum = std::strtoul(ck.c_str(), NULL, 16);


	for (int k = dSign + 1; k < starSign; k++)
	{
		ck2 ^= toCk.at(k);
	}

	strOk = (ck2 == ckSum);

	return strOk;
}



void NmeaStream::ParseNmeaSentence()
{
	int commaPos = currSentence.find(",");
	nmeaId = currSentence.substr(1, commaPos-1);
	//std::cout <<"Current "<< currSentence << std::endl;
	if (nmeaId == NMEA_GPGGA)
	{
		fillGPGGA();
	}
	else if (nmeaId == NMEA_RMC)
	{
		fillRMC();
	}
	else
	{
		// dont care?
	//	std::cout << "DontCare " << nmeaId<< std::endl;
	}




}


void NmeaStream::fillRMC()
{
	int commaPosA, commaposB;
	
	grabElement();//Header
	//std::cout << "???:" << element << std::endl;
	//item1 ---Time
	grabElement();
//	std::cout << "RMC TIme:" << element << std::endl;
	nmeaRmc.utcTime = atof(element.substr(0, 1).c_str()) * 3600
		+ atof(element.substr(2, 3).c_str()) * 60
		+ atof(element.substr(4, 5).c_str());
	//item2 ---Acivte/Void
	grabElement();
	nmeaRmc.isActive = element.at(0) == 'A' ? true :  false;
	//item3 --- lat
	grabElement();
	nmeaRmc.lat = atof(element.c_str());
	//item 4-- lat N or S
	grabElement();
	nmeaRmc.lat = (element.at(0) == 'S') ? -nmeaRmc.lat : nmeaRmc.lat;//invert if it says "S"
	// item 5 -- long 
	grabElement();
	nmeaRmc.lon = atof(element.c_str());
	//item 6 --- long E/W
	grabElement();
	nmeaRmc.lon = (element.at(0) == 'W') ? 360.0 - nmeaRmc.lon : nmeaRmc.lon;
	//item 7 --- speed over ground in knots
	grabElement();
	nmeaRmc.speed = std::atof(element.c_str())  * KNOTS_TO_MPS;
	//item 8 ---- speed heading!
	grabElement();
	nmeaRmc.heading = std::atof(element.c_str());

	//std::cout << "Rmc: " << nmeaRmc.utcTime << std::endl;
	
}
void NmeaStream::fillGPGGA()
{
	grabElement();//Header
	//item1 ---Time
	grabElement();
	nmeaGpgga.utcTime = atof(element.substr(0, 1).c_str()) * 3600
		+ atof(element.substr(2, 3).c_str()) * 60
		+ atof(element.substr(4, 5).c_str());
	
	//item2 --- lat
	grabElement();
	nmeaGpgga.lat = UnpackLatLong(element);
	//item 3-- lat N or S
	grabElement();
	nmeaGpgga.lat = (element.at(0) == 'S') ? -nmeaGpgga.lat : nmeaGpgga.lat;//invert if it says "S"
	// item 4 -- long 
	grabElement();
	nmeaGpgga.lon = UnpackLatLong(element);
	//item 5--- long E/W
	grabElement();
	nmeaGpgga.lon = (element.at(0) == 'W') ? 360.0 - nmeaGpgga.lon : nmeaGpgga.lon;
	//item 6 --- Fix Quality
	grabElement(); 
	nmeaGpgga.isActive = atoi(element.c_str()) != 0; // 0 is no position
	//item 7 ----sats tracked
	grabElement();
	//item 8 ---- HDOP
	grabElement();
	//item 9 Alt
	grabElement();
	nmeaGpgga.altitude = atof(element.c_str());
	// item 11 alt unit
	grabElement();
	if (element.compare("M"))
	{
		std::cout << "Units not in meters wtf!" << std::endl;
	}
	//item 9 Geoid
	grabElement();
	nmeaGpgga.geoidH = atof(element.c_str());
	// item 11 geoid unit
	grabElement();
	if (element.compare("M"))
	{
		std::cout << "Units not in meters wtf!" << std::endl;
	}
	
	pvtAvail_ = true; 
	//std::cout << "GPGGA: " << nmeaGpgga.utcTime << std::endl;
	if (debugOn_)
	{
		std::cout << "Lat: " << nmeaGpgga.lat <<
			"\nLong: " << nmeaGpgga.lon <<
			"\nAlt: " << nmeaGpgga.altitude <<
			"\nLong: " << nmeaGpgga.lon <<
			"\nAct: " << nmeaGpgga.isActive <<
			"\nUTC: " << nmeaGpgga.utcTime << std::endl;
	}
}

void NmeaStream::grabElement()
{
	int commaPosA;
	commaPosA = currSentence.find(",");
	element =  currSentence.substr(0,commaPosA);
	currSentence.erase(0, commaPosA+1);
	if (commaPosA == 0)
	{
		element = "qqq";
	}
	if (debugOn_)
	{

		std::cout << "curr:" << currSentence << " Element: " << element << std::endl;
	}
	// done
}


bool NmeaStream::getPVT(GpsMeasurement *gps)
{

	double cl, sl; //cos(long) sin(long)
	double ct, st; //cos(lat) sin(lat)
	double R;
	if (pvtAvail_)
	{

		pvtAvail_ = false;//consume
		if (nmeaGpgga.isActive)
		{
			//std::cout << "Lat: " << nmeaGpgga.lat << " Long: " << nmeaGpgga.lon << std::endl;
			R = REarth + (nmeaGpgga.altitude);

			cl = cosd(nmeaGpgga.lon);
			sl = sind(nmeaGpgga.lon);
			ct = cosd(nmeaGpgga.lat);
			st = sind(nmeaGpgga.lat);

			gps->time = nmeaGpgga.utcTime;
			gps->X_ECEF = R * cl*ct;
			gps->Y_ECEF = R * sl*ct;
			gps->Z_ECEF = R*st;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

float NmeaStream::UnpackLatLong(std::string ddmm)
{
	float deg;
	float minutes;
	int dotLoc;
	int minStart;
	dotLoc = ddmm.find(".");
	minStart = dotLoc - 2;
	if (minStart > 0)
	{
		deg = atof(ddmm.substr(0, minStart).c_str());
		minutes = atof(ddmm.substr(minStart, 100).c_str());//just go way past the end???
		deg = deg + (minutes*(1 / 60.0));
	}
	return deg;
}