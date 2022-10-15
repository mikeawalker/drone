#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Includes.h"
#include "KalmanFilter.h"
#include <fstream>
class Navigator 
{

public:
	Navigator();
	~Navigator();
	void Initialize();
	
	void setInput( ImuMeasurement *imuIn );
	void setInput( GpsMeasurement *gpsIn );
	void setInput( MagMeasurement *magIn );
	void setInput( DroneNavInfo *data );
	void setInput( StateVector *data );
	void setInput( CovData *data );
	void setInput(AccelVector *accelVec);

	void getOutput( StateVector *data );
	bool getOutput( FullState *data ) ;
	void setImuPosition(double r_b1,double r_b2,double r_b3);
	void setGpsPosition(double r_b1, double r_b2, double r_b3);

	void outputDebugData();
	void outputStateData();
	void outputCovData();

	static const int ERROR_STATES = 15;
	static const int GPS_MEASURES = 6;
	static const int MAG_MEASURES = 3;
	
	static const unsigned int POSITION = 0;
	static const unsigned int VELOCITY = 3;
	static const unsigned int ANGLE = 6;
	static const unsigned int ACCEL_BIAS = 9;
	static const unsigned int GYRO_BIAS = 12;

	static const unsigned int ACCEL_NOISE = 0;
	static const unsigned int GYRO_NOISE = 3;

	void SetupFirstPos(GpsMeasurement *gps);
private:
	void TimeUpdate();
	void MeasurementUpdate();
	void LinearizeEom();
	void CorrectImuToFrame();

	void setDcm() ;

	void Propegate();

	void ApplyAttitudeCorrections();
	void ApplyTranslationCorrections();
	
	void KalmanGpsUpdate();
	void KalmanMagUpdate();
	void KalmanTimeProp();

	void PredictGps();
	void PredictMag();
	void CheckInit();
	void SetupFirstOrient(MagMeasurement *mag);
	void SetupFirstBias(ImuMeasurement *imu);
	void EstimateGravityVector();
	// time

	double currTime_;
	double lastTime_;
	double utcTime_;

	// Error States Stuff
	Eigen::MatrixXd P_;
	Eigen::MatrixXd dx_;
	Eigen::MatrixXd dxUp_;
	Eigen::MatrixXd G_;
	Eigen::MatrixXd A_;
	Eigen::MatrixXd Q_;

	// GPS KF Update Matrix
	Eigen::MatrixXd C_gps;
	Eigen::MatrixXd K_gps;
	Eigen::VectorXd yGps_;
	Eigen::MatrixXd R_gps;

	Eigen::VectorXd yGpsMeasure_;
	// Magno KF Update
	Eigen::MatrixXd C_mag;
	Eigen::MatrixXd K_mag;
	Eigen::VectorXd yMag_;
	Eigen::MatrixXd R_mag;
	Eigen::VectorXd yMagMeasure_;
	
	// Sensor Locations
	Eigen::Vector3d gpsLoc_;
	Eigen::Vector3d imuLoc_;


	// Best State Estimates
	Eigen::Vector3d rHat_;
	Eigen::Vector3d vHat_;
	Eigen::Vector4d qHat_;
	Eigen::Vector3d aBias_;
	Eigen::Vector3d wBias_;

	// IMU Stuff
	Eigen::Vector3d wMeasure_;
	Eigen::Vector3d wTrue_;
	Eigen::Vector3d aMeasure_;
	Eigen::Vector3d aTrue_;
	
	


	Eigen::Matrix3d dcmC2b_;
	Eigen::Matrix3d dcmMag2_; // orientation of second magnetometer
	Eigen::Vector3d g0_;
	Eigen::Vector3d accelEstEnu_;
	Eigen::Vector3d gravEstimate_;
	// Rotation ECEF -> LOCAL
	Eigen::Matrix3d dcmEcef2Local_;
	Eigen::Vector3d earthSurfaceENU_;

	int propegateSteps;
    bool newStateReady_;
	bool firstOrientRcv_;
	bool firstPosRcv_;
	bool firstAccelRcv_;
	bool firstBiasRcv_;
	bool navInit_;
	bool debugOn;
	bool debugPrint;
	FILE *covFile;
	FILE *stateFile;
	FILE *debugFile;

protected:
};


#endif