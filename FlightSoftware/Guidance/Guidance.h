#ifndef GUIDANCE_H_
#define GUIDANCE_H_

#include "Includes.h"
#include "LookupTable.h"
#include "PID.h"
#include <Eigen/Dense>
#include <stdio.h>
#include <fstream>
class Guidance
{

public:
	Guidance();
	~Guidance();
	void Reset();
	void Iterate();
	void LoadTrajectory(std::string fname);
	void setInput( FullState *state);
	void setInput(StabilityCmd *cmd );
	void setInput(LineCmd *cmd);
	void setInput(LiftoffData *cmd);
	void setInput(LandingData *cmd);
	void setInput(ReturnToBase *cmd);
	void setInput(WaypointLocation *data);
	void setInput(IdleCmd *data);
	//void setState( FullState *state);
	bool getOutput( GuidanceCmd *cmd );
	bool getOutput( GuidanceReport *data);
	

	void setGains(PidGain X, PidGain Y, PidGain H);
	void setDownsample(double downSample);
	void getDebug( double *debugO); 
private:
	void GroundSpinUp();
	void rotateErrors();
	void calcCurvature();
	void populateCommandState();
	void populateFromWaypoint();
	void populateDirectLine();
	void populateHold();
	void populateParabola();
	void populateConstAccel();

	PID<double> posX;
	PID<double> posY;
	PID<double> posH;

	PidGain GainX;
	PidGain GainY;
	PidGain GainH;

	FullState myState;
	FullState myLastState;
	FullState myLastState2;

	GuidanceCmd myGuideCmd;


	LookupTable xTraj;
	LookupTable yTraj;
	LookupTable hTraj;
	LookupTable vxTraj;
	LookupTable vyTraj;


	//liftoff
	ParabolicTraj myParabolic;
	LineTraj myLine;

	std::vector<double> xTable; 
	std::vector<double> yTable; 
	std::vector<double> hTable; 
	std::vector<double> vxTable;
	std::vector<double> vyTable;
	std::vector<double> tTable;
	
	// Errors
	double Xerr;
	double Yerr;
	double Zerr;

	double VXerr;
	double VYerr;
	double VZerr;

	double yawCmd; // to allow yaw skewing during a hold point;
	// Rotated Errors
	double waypointEpoch_;


	Eigen::Matrix2d toTrackFrame;
	Eigen::Vector2d re;
	Eigen::Vector2d ve;
	Eigen::Vector2d acurve;
	Eigen::Vector3d accelCmd;

	
	bool initialized;
	double debug[3];
	double VxCmd, VyCmd;
	double xCmd, yCmd, hCmd;
	Eigen::Vector3d stabilityCmd;
	bool newCmdReady;
	bool reportReady;
	StateTypes::GuidanceModes guideMode;

	unsigned int stateCount;
	unsigned int StatePerCmd;

	IdleCmd idleCmd_;

#ifdef DEBUG_DATA
	FILE *debugFp;
#endif


protected:

};

#endif