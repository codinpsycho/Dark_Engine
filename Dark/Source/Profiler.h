#pragma once

#include "Timer.h"

class CProfiler
{
public:
	CProfiler(void);
	~CProfiler(void);

	static float GetCpuFrequency();
	static void StartProfiling();
	static double StopProfiling();		//Returns passed Cpu Cycles
	static float GetCpuCycles();

private:
	static double m_cpuFrequency;
	static Timer m_timer;		//For Queryperformance functionality
	static float m_cpuCycles;
	static double m_deltaTime;



};
