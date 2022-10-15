#include "MyTime.h"


void MyTime::sSleep(unsigned int sec)
{
#ifdef WINDOWS_TIME
	Sleep(sec * 1000);
#else
	usleep(sec * 1000000);
#endif
}

void MyTime::mSleep(unsigned int msec)
{
#ifdef WINDOWS_TIME
	Sleep(msec);
#else
	usleep(msec * 1000);
#endif
}

void MyTime::uSleep(unsigned int usec)
{
#ifdef WINDOWS_TIME
	Sleep(1);
#else
	usleep(usec);
#endif
}
