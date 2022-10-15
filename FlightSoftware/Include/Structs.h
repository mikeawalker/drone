#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <Eigen/Dense>


typedef struct
{
	double cov;
} CovArray;
typedef struct
{
	float utcTime;
	bool isActive;
	float lat;
	float lon;
	float speed;
	float heading;
} NmeaRmc;
typedef struct
{
	float utcTime;
	bool isActive;
	float lat;
	float lon;
	float altitude;
	float geoidH;
} NmeaGpgga;
typedef struct
{
	Eigen::Vector3d r;
	Eigen::Vector3d v;
	Eigen::Vector4d q;
	Eigen::Vector3d aBias;
	Eigen::Vector3d wBias;
} StateVector;


typedef struct CovData
{
	Eigen::VectorXd Covs;
	CovData()
	{
		Covs = Eigen::VectorXd::Zero(15);
	}
} CovData;
typedef struct ApGain
{
	double Ka;
	double Kw;
	double Ksyn;
} ApGains;


typedef struct PidGain
{
	double Ki;
	double Kp;
	double Kd;

} PidGain;

typedef struct
{
	double liftOffAltitude;
	double liftOffDuration;
	double landingAvgVel;
	double returnAvgVel;
	double groundIdleAccel;
}FlightCmds;
typedef struct DroneNavInfo
{
	Eigen::Vector3d gpsPosVar;
	Eigen::Vector3d gpsVelVar;
	Eigen::VectorXd magVar;
	Eigen::Vector3d accelVar;
	Eigen::Vector3d gyroVar;
	DroneNavInfo()
	{
		magVar = Eigen::VectorXd::Zero(6);
		gpsPosVar = Eigen::VectorXd::Zero(3);
		gpsVelVar = Eigen::VectorXd::Zero(3);
		magVar = Eigen::VectorXd::Zero(6);
		accelVar = Eigen::VectorXd::Zero(3);
		gyroVar = Eigen::VectorXd::Zero(3);
	}
} DroneNavInfo;
typedef struct
{
	double X_ECEF;
	double Y_ECEF;
	double Z_ECEF;
	double time;

} GpsMeasurement;

typedef struct
{
	double a_b1;
	double a_b2;
	double a_b3;
	double w_b1;
	double w_b2;
	double w_b3;
	double time;
} ImuMeasurement;


typedef struct
{
	double mag1_x;
	double mag1_y;
	double mag1_z;
	double time;
} MagMeasurement;




typedef struct
{

	Eigen::Vector3d accel_cmd;
	Eigen::Vector3d v_cmd;
	double yawCmd;
	bool reset;
	bool runAp;

} GuidanceCmd;

typedef struct
{
	Eigen::Vector3d pos;
	Eigen::Vector3d vel;
	Eigen::Vector4d q;
	Eigen::Vector3d omega;
	Eigen::Vector3d accel;
	double time;
} FullState;

typedef struct
{
	double pos[3];
	double vel[3];
	double quat[4];
	double omega[3];
	double time;

} SimInput;


typedef struct
{
	double mass;
	double J_motor;
	Eigen::Matrix3f Inertia;

} DroneProperties;

typedef struct
{
	double rate1;
	double rate2;
	double rate3;
	double rate4;

} BladeCmd;


typedef struct
{
	double time;
	double r[3];
	double v[2];
} Trajectory;

typedef struct
{
	bool start;
} TimerSetup;

typedef struct
{
	float ax;
	float ay;
	float az;
} AccelVector;

typedef struct
{
	float magx;
	float magy;
	float magz;
} MagVector;

typedef struct
{
	float wx;
	float wy;
	float wz;
}GryoVector;

typedef struct
{
	Eigen::Vector3d stabilityPos;
} StabilityCmd;
typedef struct
{
	Eigen::Vector3d lineCmd;
	double lineTime;
} LineCmd;

typedef struct
{
	BladeCmd bladeCmd;
	GuidanceCmd guideCmd;
	double quat[3];

} ToSimData;

typedef struct
{
	double time;
	double duration;
	double holdAltitude;
} ReturnToBase;

typedef struct
{
	double duration;
	double time;
	double hFinal;
} LiftoffData;

typedef struct
{
	double hStart;
	double time;
	double duration;
} LandingData;

typedef struct
{
	double t0;
	double duration;
	double y0[3];
	double yHold[3];
	double v0[3];
	double a[3];
}ParabolicTraj;

typedef struct
{
	Eigen::Vector3d lineStart;
	Eigen::Vector3d lineEnd;
	Eigen::Vector3d lineVel;
	double lineEpoch;
	double duration;
}LineTraj;

typedef struct
{
	char waypointFile[50];
} WaypointLocation;
enum UiCmd
{
	NONE = 0,
	TAKEOFF,
	START,
	RTB,
	LAND,
	OVERRIDE,
	UP,
	DOWN,
	NORTH,
	EAST,
	SOUTH,
	WEST,
	KILL
};
namespace Tm
{

	typedef enum
	{
		AIR,
		GROUND
	}TmNode;
	typedef enum
	{
		GYRO = 0,
		EKF,
	} TmIds;
}
typedef struct
{
	UiCmd cmd;
} UserCmd;

typedef struct
{
	double time;
} BeatTime;



namespace StateTypes
{
	enum FlightState
	{
		STARTUP =0,
		GROUND_WAITING,
		LIFTOFF,
		PREPROG_WAYPOINT,
		STABILIZE,
		POINT_TO_BASE,
		RETURN_TO_BASE,
		LANDING,
		OVERRIDE,
		NUM_FLIGHT_STATES		
	};

	enum GuidanceModes
	{
		WAYPOINT = 0,
		LINE,
		HOLDPOINT,
		PARABOLA,
		SKEW,
		GROUND_HOLD,
		CONST_ACCEL,
		NONE
	};
	
	enum  AutoPilotModes
	{
		AP_WAIT = 0,
		AP_SPINUP,
		AP_STANDBY,
		AP_CMD
	};
};


typedef struct
{
	StateTypes::GuidanceModes mode;
}GuidanceReport;
typedef struct
{
	StateTypes::AutoPilotModes mode;
}AutopilotReport;

typedef struct
{
	double accel;
}IdleCmd;

typedef struct DebugInfo
{
	std::string title;
	double *data;

	DebugInfo(std::string str, double *d) : title(str), data(d) {}
} DebugInfo;
#endif