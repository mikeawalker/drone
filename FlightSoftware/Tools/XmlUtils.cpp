#include  "XmlUtils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>





DroneNavInfo XmlUtils::GetNavInfo(std::string XmlFile)
{
	using boost::property_tree::ptree;

	DroneNavInfo info;
	ptree pt;
	ptree accelTree;
	ptree gpsTree;
	ptree mag1Tree;
	ptree mag2Tree;
	ptree gyroTree;
	read_xml(XmlFile, pt);

	accelTree = pt.get_child("drone.Devices.Accel");
	gpsTree = pt.get_child("drone.Devices.Gps");
	gyroTree = pt.get_child("drone.Devices.Gyro");
	mag1Tree = pt.get_child("drone.Devices.Mag1");
	mag2Tree = pt.get_child("drone.Devices.Mag1");
	

		info.accelVar << accelTree.get<double>("NoiseVariance.x"),
		accelTree.get<double>("NoiseVariance.y"),
		accelTree.get<double>("NoiseVariance.z");

		info.gyroVar << gyroTree.get<double>("NoiseVariance.x"),
			gyroTree.get<double>("NoiseVariance.y"),
			gyroTree.get<double>("NoiseVariance.z");
		info.magVar << mag1Tree.get<double>("NoiseVariance.x"),
			mag1Tree.get<double>("NoiseVariance.y"),
			mag1Tree.get<double>("NoiseVariance.z"),
			mag2Tree.get<double>("NoiseVariance.x"),
			mag2Tree.get<double>("NoiseVariance.y"),
			mag2Tree.get<double>("NoiseVariance.z");

		info.gpsPosVar << gpsTree.get<double>("PosNoiseVariance.x"),
			gpsTree.get<double>("PosNoiseVariance.y"),
			gpsTree.get<double>("PosNoiseVariance.z");
		info.gpsVelVar << gpsTree.get<double>("VelNoiseVariance.x"),
			gpsTree.get<double>("VelNoiseVariance.y"),
			gpsTree.get<double>("VelNoiseVariance.z");



	return info;
}


void XmlUtils::GetApGains(std::string XmlFile, ApGain &roll, ApGain &pitch, ApGain &yaw)
{
	using boost::property_tree::ptree;
	ptree pt;
	ptree apTree;
	
	read_xml(XmlFile, pt);

	apTree = pt.get_child("drone.Control.Autopilot");

	roll.Ka = apTree.get<double>("Roll.Ka");
	roll.Kw = apTree.get<double>("Roll.Kw");
	roll.Ksyn = apTree.get<double>("Roll.Ksyn");
	pitch.Ka = apTree.get<double>("Pitch.Ka");
	pitch.Kw = apTree.get<double>("Pitch.Kw");
	pitch.Ksyn = apTree.get<double>("Pitch.Ksyn");
	yaw.Ka = apTree.get<double>("Yaw.Ka");
	yaw.Kw = apTree.get<double>("Yaw.Kw");
	yaw.Ksyn = apTree.get<double>("Yaw.Ksyn");
	
}

void XmlUtils::GetSpinUp(std::string xmlFile, double &delta, double &spin0)
{
	

	using boost::property_tree::ptree;
	ptree pt;
	ptree spinTree;
	read_xml(xmlFile, pt);
	spinTree = pt.get_child("drone.Control.Autopilot.SpinUp");

	delta = spinTree.get < double >("DeltaThrottle");
	spin0 = spinTree.get < double >("StartThrottle");
}


void XmlUtils::GetGuidanceGains(std::string xmlFile, PidGain &Horizontal, PidGain &Vert, double &downSample)
{

	using boost::property_tree::ptree;
	ptree pt;
	ptree guideTree;
	read_xml(xmlFile, pt);
	guideTree = pt.get_child("drone.Control.Guidance");



	Horizontal.Kd = guideTree.get<double>("Position.Kd");
	Horizontal.Ki = guideTree.get<double>("Position.Ki");
	Horizontal.Kp = guideTree.get<double>("Position.Kp");
	Vert.Kd = guideTree.get<double>("Hover.Kd");
	Vert.Ki = guideTree.get<double>("Hover.Ki");
	Vert.Kp = guideTree.get<double>("Hover.Kp");
	downSample = guideTree.get<double>("CommandsPerImu");

}


FlightCmds XmlUtils::GetFlightCmds(std::string xmlFile)
{
	FlightCmds out;
	using boost::property_tree::ptree;
	ptree pt;
	ptree flightTree;

	read_xml(xmlFile, pt);
	flightTree = pt.get_child("drone.Flight");


	out.liftOffAltitude = flightTree.get<double>("Takeoff.hFinal");
	out.liftOffDuration = flightTree.get<double>("Takeoff.duration");
	out.landingAvgVel = flightTree.get < double>("Landing.AvgVelocity");
	out.returnAvgVel = flightTree.get < double>("Landing.AvgVelocity");
	out.groundIdleAccel = flightTree.get < double>("GroundIdle.Accel");
	return out;
}

std::string XmlUtils::GetMag1FileName(std::string xmlFile)
{
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(xmlFile, pt);
	return pt.get<std::string>("drone.Devices.Mag1.CalDataFile");
}
std::string XmlUtils::GetMag2FileName(std::string xmlFile)
{
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(xmlFile, pt);
	return pt.get<std::string>("drone.Devices.Mag2.CalDataFile");
}