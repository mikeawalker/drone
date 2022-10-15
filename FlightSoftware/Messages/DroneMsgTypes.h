#ifndef DRONEMSGTYPES_H
#define DRONEMSGTYPES_H

#include "Structs.h"
namespace DroneMsgTypes
{
	static const unsigned int BladeCmdMsgId = 0x0010;
	static const unsigned int EkfStateMsgId = 0x0011;
	static const unsigned int GpsPvtMsgId = 0x0012;
	static const unsigned int GuideMsgId = 0x0013;
	static const unsigned int ImuMsgId = 0x0014;
	static const unsigned int MagMsgId = 0x0015;
	static const unsigned int StabilityMsgId = 0x0016;
	static const unsigned int CovMsgId = 0x0017;
	static const unsigned int GpsAccelMsgId = 0x0018;
	static const unsigned int LiftoffMsgId =  0x0019;
	static const unsigned int RtbMsgId = 0x0020;
	static const unsigned int UserCmdMsgId = 0x0021;
	static const unsigned int LandingMsgId = 0x0022;
	static const unsigned int GuidanceReportMsgId = 0x0023;
	static const unsigned int AutopilotReportMsgId = 0x0024;
	static const unsigned int WaypointMsgId = 0x0025;
	static const unsigned int IdleMotorMsgId = 0x0026;
	static const unsigned int Timer_1000HzMsgId = 0x0200;
	static const unsigned int Timer_5HzMsgId = 0x0201;
	static const unsigned int Timer_30HzMsgId = 0x0202;
	static const unsigned int TimerSetupMsgId = 0x0203;
	static const unsigned int MagInterruptId =  0x0300;
	static const unsigned int TmHeartBeatId =  0x03001;
};

#endif