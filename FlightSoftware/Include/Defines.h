#ifndef DEFINES_H
#define DEFINES_H


#define PI   3.14159265358979
#define DEG2RAD 0.0174532925199433
#define RAD2DEG 57.2957795130823


#define ZERO_TOL 0.000001
#define G0 9.80665 //Defined standard grabity
#define REarth 6378000.0 // m

static const double GS_DELTA_POS = 0.5;

#define GPS_POWER_PIN  "18"
#define IMU_POWER_PIN  "13"

#define GPS_ON "0"
#define GPS_OFF "1"

#define GPIO_OUT "out"
#define GPIO_IN  "in"


	#define WINDOWS_TIME

	//#define LINUX_DEVICE 



//#define REAL_DEVICE
#define ETHERNET_DEVICE
//#define DEBUG_DATA 0

#define KNOTS_TO_MPS  1.0;

#define NMEA_GPGGA  "GPGGA"
#define NMEA_RMC  "GPRMC"

#define LINK_GYRO "GYR"
#define LINK_HEARTBEAT "HEARTBEAT"
#define LINK_CMD "COMMAND"
#define LINK_EKF "EKF"
#define LINK_IMU "IMU"
#define LINK_MAG "MAG"
#define LINK_GPS "GPS"

#endif
