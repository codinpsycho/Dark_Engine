#pragma once

#include <windows.h>


class Timer
{
public:

	Timer(void)
	{
		//get the CPU frequency i.e no. of counts in 1 second
		QueryPerformanceFrequency(&m_frequency);
	}
	void Start()
	{
		//get the starting count
		QueryPerformanceCounter(&m_start);
	}
	void Stop()
	{
		//get the ending count
		QueryPerformanceCounter(&m_stop);
	}
	double GetDeltaTime()
	{
		//get number of ticks passed
		double ticks = (double)m_stop.QuadPart - (double)m_start.QuadPart;
		 return ticks/(double)m_frequency.QuadPart;
	}

	LARGE_INTEGER GetTicks()
	{
		//get number of ticks passed
		double ticks = (double)m_stop.QuadPart - (double)m_start.QuadPart;
	}

	virtual ~Timer(void)
	{
	}

private:
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_stop;

};
