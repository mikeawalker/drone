#ifndef AUTOPILOT_H_
#define AUTOPILOT_H_



#include "Includes.h"
#include "Integrator.h"
#include "Tools.h"
#include <vector>
class AutoPilot
{
public:
	AutoPilot();
	~AutoPilot();

	void Reset();
	void Iterate();
	void setInput(FullState *inState);
	void setInput(GuidanceCmd *inCmd);
	void setInput(DroneProperties *in);
	bool getOutput(BladeCmd *out);
	bool getOutput(AutopilotReport *out);
	void getCommand( GuidanceCmd *out );

	void getM( double *M);
	void getR( double *R);

	void setGains(ApGain roll, ApGain pitch, ApGain yaw);
	void setSpinUp(double spinUpDelta,double spinUp0);
private:
	void LoadGains(std::string fname);
	void scheduleGains();
	void runPitchAp();
	void runRollAp();
	void runYawAp();
	void convertToCommands();
	void calcFrames();
	void accelFrameChange();
	void operate();
	void SpinUp();
	void SpinIdle();
	double dT_;
	Eigen::Matrix3d quatToDcm(const Eigen::Vector4d &q);

	Integrator<double> pitchIntegrator;
	Integrator<double> rollIntegrator;
	Integrator<double> yawIntegrator;
	bool useDebug_;
	FILE *debugFp;

	//commands
	double M2Cmd_;
	double M1Cmd_;
	double M3Cmd_;
	double F0;
	//Gains
	double KaQ;
	double KaY;
	double KaR;
	double KaPitch_;
	double KsynPitch_;
	double KwPitch_;
	double KaRoll_;
	double KsynRoll_;
	double KwRoll_;
	double KaYaw_;
	double KsynYaw_;
	double KwYaw_;
	// Spin Up params
	double ThrottleAccum;
	double RunUpThrottle0;
	double RunUpThrottleDelta;
	double AccelToThrottle;
	bool RunUpComplete;
	bool sendReport;
	//  angular velocity states 
	double w1;
	double w2;
	double w3;
	// yaw states
	double yaw;
	double yawLast;
	double yawCmd;
	double yawCmdLast;

	//
	Eigen::Vector3d accelTrack_;
	Eigen::Vector3d accelCmdTrack_;
	Eigen::Vector3d velCmd_;
	Eigen::Matrix3d dcmLocalToTrack_;
	Eigen::Matrix3d dcmBToTrack_;
	Eigen::Matrix3d dcmCToB_;
	//
	BladeCmd myCmd_;
	bool newApCmdRdy_;
	bool guideInit;
	bool stateInit;
	//
	FullState myState_;
	DroneProperties myDrone_;
	GuidanceCmd	myGuidance_;


	StateTypes::AutoPilotModes mode;

	double inTrackAccel_;
	double inTackAccelCmd_;

	double xTrackAccel_;
	double xTrackAccelCmd_;

	double throttleCmd;

	double yawError;


	double rollIntIn;
	double rollIntOut;
	double debugV[40];
	bool apInit;

	void CheckInit();
	void ConstrainYawError();

	std::vector<DebugInfo*> debug;
	void SetupDebug();
	void PrintDebug();
protected:


};
#endif