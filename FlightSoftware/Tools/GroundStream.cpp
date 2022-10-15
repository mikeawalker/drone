#include "GroundStream.h"


const std::string GroundStream::a2gPrefix = "$AR:";
const std::string GroundStream::g2aPrefix = "$GD:";
const std::string GroundStream::postfix = "**";

GroundStream::GroundStream(bool air)
{
	inSentence.reserve(300);
	outSentence.reserve(300);
	myPrefix.reserve(20);
	if (air)
	{
		myPrefix = a2gPrefix;
		inPrefix = g2aPrefix;
	}
	else
	{
		myPrefix = g2aPrefix;
		inPrefix = a2gPrefix;
	}
	if (!air)
	{
		fileOut = true;
		stateFile = fopen("stateTm.txt", "wt");
		fprintf(stateFile,"time,x,y,z,vx,vy,vz,q1,q2,q3,q4,a1,a2,a3,w1,w2,w3\n");
		fclose(stateFile);
		imuFile   = fopen("imuTm.txt", "wt");
		fprintf(imuFile, "time,a1,a2,a3,w1,w2,w3\n");
		fclose(imuFile);
		magFile = fopen("magTm.txt", "wt");
		fprintf(magFile, "time,m1,m2,m3\n");
		fclose(magFile);
		gpsFile = fopen("gpsTm.txt", "wt");
		fprintf(gpsFile, "time,XE,YE,ZE\n");
		fclose(gpsFile);
	}
}

GroundStream::~GroundStream()
{
	if (fileOut)
	{
		fclose(imuFile);
		fclose(stateFile);
	}
}



void GroundStream::append(char *buff, int bytes)
{
	inSentence.append(buff, bytes);
}



void GroundStream::parseAll()
{
	while (parseFirstStream())
	{
	}
}

bool GroundStream::parseFirstStream()
{
	int dsign1;
	int star;
	int colon;
	std::string tmpSentence;
	Tm::TmIds tmId;
	dsign1 = inSentence.find(inPrefix);
	colon = inSentence.find(":", dsign1 + 1);
	star = inSentence.find(postfix, colon + 1);
	if (dsign1 > -1 && star > -1 & colon > -1)
	{
		tmpSentence = inSentence.substr(dsign1, star + 2 + postfix.length() - dsign1);
		if (checksumOk(tmpSentence))
		{
			parseInSentence();
			inSentence.erase(0, star + 2 + postfix.length() - dsign1);

		}
		else
		{
			std::cout << "Bad TM CkSum" << std::endl;
			inSentence.clear();
			
		}

	}
	else
	{
		return false;
	}
	return true;
}

void GroundStream::parseInSentence()
{
	int comma = inSentence.find(",");
	int colon = inSentence.find(":");
	int star = inSentence.find(postfix);
	void *dataStart;
	const char *sent;
	std::string id;
	id = inSentence.substr(colon+1, comma - colon-1);
	
	//std::cout <<"Current "<< currSentence << std::endl;
	std::cout << inSentence.length() << " " << inSentence.size() << std::endl;

	if (id == LINK_GYRO)
	{
		memcpy(&gyroVec, &inSentence[comma+1], sizeof(gyroVec));
		gyroReady = true;;
	}
	else if (id == LINK_EKF)
	{
		memcpy(&droneState, &inSentence[comma + 1], sizeof(droneState));
		stateAvail = true;

	}
	else if ( id == LINK_IMU )
	{
		memcpy(&droneImu, &inSentence[comma + 1], sizeof(double)*7);
		imuAvail = true;
	}
	else if (id == LINK_MAG)
	{
		memcpy(&droneMag, &inSentence[comma + 1], sizeof(droneMag));
		magAvail = true;
	}
	else if (id == LINK_CMD)
	{
		memcpy(&droneCmd, &inSentence[comma + 1], sizeof(UserCmd));
		cmdAvail = true;

	}
	else if (id == LINK_GPS)
	{
		memcpy(&droneGps, &inSentence[comma + 1], sizeof(GpsMeasurement));
		gpsAvail = true;
	}
	else if (id == LINK_HEARTBEAT)
	{
		heartBeatAvail = true;
	}
	else
	{
		// dont care?
			std::cout << "DontCare " << id<< std::endl;
	}




}

unsigned char GroundStream::generateCk(std::string in)
{
	unsigned char ck2 = 0;
	int dSign;
	int starSign;
	dSign = in.find(a2gPrefix);
	starSign = in.find(postfix);
	for (int k = dSign + 1; k < starSign; k++)
	{
		ck2 ^= in.at(k);
	}
	return ck2;
}

bool GroundStream::checksumOk(std::string toCk)
{
	int len = toCk.length();
	unsigned char ckReal;
	int dSign;
	int starSign;
	int ckSum;
	int ck2 = 0;
	bool strOk;
	std::string ck;

	dSign = toCk.find(a2gPrefix);
	starSign = toCk.find(postfix);
	ck = toCk.substr(starSign + postfix.length(), 2);
	ckSum = std::strtoul(ck.c_str(), NULL, 16);
	ckReal = (generateCk(toCk));
	ck2 = static_cast<int>(ckReal);

	strOk = (ck2 == ckSum);

	return strOk;
}


void GroundStream::formatMsg(void *data, int msize, std::string typeId)
{
	
	unsigned char cks;
	char a[4];
	outSentence.clear();
	outSentence.append(myPrefix.c_str(), myPrefix.size());
	outSentence.append(typeId.c_str(), typeId.size());
	outSentence.append(",", 1);
	outSentence.append((char*)data, msize);
	outSentence.append(postfix.c_str(), postfix.size());
	
	
	cks = generateCk(outSentence);
#ifdef LINUX_DEVICE
	sprintf(a, "%02x", cks);
#else
	sprintf_s(a, "%02x", cks);
#endif
	outSentence.append(a,2);
//	std::cout << "Out: " << outSentence << std::endl;

}

bool GroundStream::pullGyro(GryoVector *vec)
{
	if (gyroReady)
	{
		gyroReady = false;
		*vec = gyroVec;
		return true;
	}

}

bool GroundStream::pullHeartBeat(BeatTime &heartBeat)
{
	if (heartBeatAvail)
	{
		heartBeatAvail = false;
		return true;
	}
	return false;
}
bool GroundStream::pullCommand(UserCmd &cmd)
{
	if (cmdAvail)
	{
		cmd = droneCmd;
		cmdAvail = false;
		return true;
	}
	return false;
}

bool GroundStream::pullState(FullState &cmd)
{
	if (stateAvail)
	{
		cmd = droneState;
		stateAvail = false;
		if (fileOut)
		{
			StateToFile();
		}
		return true;
	}
	return false;
}

bool GroundStream::pullImu(ImuMeasurement &cmd)
{
	if (imuAvail)
	{
		cmd = droneImu;
		imuAvail = false;
		if (fileOut)
		{
			ImuToFile();
		}
		return true;
	}
	return false;
}
bool GroundStream::pullMag(MagMeasurement &cmd)
{
	if (magAvail)
	{
		cmd = droneMag;
		magAvail = false;
		if (fileOut)
		{
			MagToFile();
		}
		return true;
	}
	return false;
}


bool GroundStream::pullGps(GpsMeasurement &gps)
{
	if (gpsAvail)
	{
		gps = droneGps;
		gpsAvail = false;
		if (fileOut)
		{
			GpsToFile();
		}
		return true;
	}
	return false;
}
void GroundStream::ImuToFile()
{

	imuFile = fopen("imuTm.txt", "at");
	fprintf(imuFile , "%f,", droneImu.time);
	fprintf(imuFile, "%f,%f,%f,", droneImu.a_b1, droneImu.a_b2, droneImu.a_b3);
	fprintf(imuFile, "%f,%f,%f,", droneImu.w_b1, droneImu.w_b2, droneImu.w_b3);
	fprintf(imuFile, "\n");
	fclose(imuFile);
}

void GroundStream::StateToFile()
{
	stateFile = fopen("stateTm.txt", "at");
	fprintf(stateFile, "%f", droneState.time);
	fprintf(stateFile, ",%f,%f,%f", droneState.pos(0), droneState.pos(1), droneState.pos(2));
	fprintf(stateFile, ",%f,%f,%f", droneState.vel(0), droneState.vel(1), droneState.vel(2));
	fprintf(stateFile, ",%f,%f,%f,%f", droneState.q(0), droneState.q(1), droneState.q(2), droneState.q(3) );
	fprintf(stateFile, ",%f,%f,%f", droneState.accel(0), droneState.accel(1), droneState.accel(2));
	fprintf(stateFile, ",%f,%f,%f", droneState.omega(0), droneState.omega(1), droneState.omega(2));
	fprintf(stateFile, "\n");
	fclose(stateFile);
}

void GroundStream::MagToFile()
{
	magFile = fopen("magTm.txt", "at");
	fprintf(magFile, "%f", droneMag.time);
	fprintf(magFile, ",%f,%f,%f", droneMag.mag1_x, droneMag.mag1_y, droneMag.mag1_z);
	fprintf(magFile, "\n");
	fclose(magFile);


}

void GroundStream::GpsToFile()
{

	gpsFile = fopen("gpsTm.txt", "at");
	fprintf(gpsFile, "%f", droneGps.time);
	fprintf(gpsFile, ",%f,%f,%f", droneGps.X_ECEF, droneGps.Y_ECEF, droneGps.Z_ECEF);
	fprintf(gpsFile, "\n");
	fclose(gpsFile);

}