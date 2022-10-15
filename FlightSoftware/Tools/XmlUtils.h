#ifndef XmlUtils_H
#define XmlUtils_H

#include "Structs.h"

namespace XmlUtils
{


	DroneNavInfo GetNavInfo(std::string xmlFile);
	FlightCmds GetFlightCmds(std::string xmlFile);

	void GetApGains(std::string xmlFile, ApGain &roll, ApGain &pitch, ApGain &yaw);
	void GetSpinUp(std::string xmlFile, double &delta, double &spin0);
	void GetGuidanceGains(std::string xmlFile, PidGain &Horizontal, PidGain &Vert, double &downsample);

	std::string GetMag1FileName(std::string xmlFile);
	std::string GetMag2FileName(std::string xmlFile);


}
#endif