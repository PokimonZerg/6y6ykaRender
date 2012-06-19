#include <windows.h>
#include "timer.h"

Timer::Timer()
{
	LARGE_INTEGER t;

	QueryPerformanceFrequency(&t);
	freq = t.QuadPart;

	QueryPerformanceCounter(&t);
	last = t.QuadPart;
}

Timer::~Timer()
{
}

double Timer::Update()
{
	LARGE_INTEGER t;
	double d;

	QueryPerformanceCounter(&t);
	d = (double)(t.QuadPart - last) / freq;
	last = t.QuadPart;

	return d;
}