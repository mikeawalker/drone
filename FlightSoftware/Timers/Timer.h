#ifndef TIMER_H
#define TIMER_H

#include "Block.h"

#include "TimerSetupMsg.h"
#include "Timer_1000HzMsg.h"
#include "Timer_30HzMsg.h"

class Timer : public Block
{
public:
	Timer(int to, boost::mutex *in);
	~Timer();
	void update();

private:
	int timeoutMs;
	boost::mutex *wakeup;
	boost::posix_time::time_duration sleepTime_;
	std::string timerId;
protected:
};
#endif
