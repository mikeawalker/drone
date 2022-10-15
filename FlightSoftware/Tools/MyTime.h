#ifndef MYTIME_H
#define MYTIME_H

#include "Defines.h"
#ifdef WINDOWS_TIME
	#include <windows.h>
#else
#include "boost/date_time/posix_time/posix_time.hpp"
#endif

namespace MyTime
{
	void mSleep(unsigned int msec);
	void sSleep(unsigned int sec);
	void uSleep(unsigned int usec);
};

#endif
