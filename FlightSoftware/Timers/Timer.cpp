#include "Timer.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include "MyTime.h"
#include <iostream>
Timer::Timer(int to, boost::mutex *in) : Block("Timer", 10, 10)
{
	wakeup = in;
	timeoutMs = to;
	sleepTime_ = boost::posix_time::milliseconds(1);
}

Timer::~Timer()
{

}


void Timer::update()
{
	MyTime::mSleep(timeoutMs);
	wakeup->unlock();
	//std::cout << " Timer expire " << std::endl;
	mtx.unlock();

}

