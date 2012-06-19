#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer();

	~Timer();

	double Update();

private:
	long long last;
	long long freq;
};

#endif