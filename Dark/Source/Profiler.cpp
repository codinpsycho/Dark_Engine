#include "Profiler.h"



//Definitions
double CProfiler::m_cpuFrequency = 0;
Timer CProfiler::m_timer ;		//For Queryperformance functionality
float CProfiler::m_cpuCycles = 0;
double CProfiler::m_deltaTime = 0;



CProfiler::CProfiler(void)
{
	m_cpuFrequency = GetCpuFrequency() * 10000000;		//To convert into MHZ
	m_timer.Start();
}

CProfiler::~CProfiler(void)
{
}

void CProfiler::StartProfiling()
{
	m_timer.Start();
}

double CProfiler::StopProfiling()
{
	m_timer.Stop();
	return m_deltaTime = m_timer.GetDeltaTime();

}

float CProfiler::GetCpuCycles()
{
	return m_cpuCycles = m_deltaTime * (1/m_cpuFrequency);
}

//Return 0.0f if not able to find CPU frequency
float CProfiler::GetCpuFrequency()
{
#if defined(WIN32)
	HKEY	key;
	DWORD	freq_mhz;

	LONG rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		LPCSTR("Hardware\\Description\\System\\CentralProcessor\\0"), 
		0, 
		KEY_READ, 
		&key);
	if (rc == ERROR_SUCCESS) 
	{
		DWORD dummy = sizeof(DWORD);
		rc = RegQueryValueEx(key, 
			LPCSTR("~MHz"),
			0,
			0,
			(LPBYTE)(&freq_mhz), 
			&dummy);
		RegCloseKey(key);
	}

	if (rc != ERROR_SUCCESS) 
		return 0.0f;
	//else
	return (float)freq_mhz;

#elif __APPLE__
	FILE *f = popen("sysctl hw.cpufrequency", "r");

	if (f) {
		bool  bingo = false;
		float freq_mhz;
		char  line[256];
		memset(&line, 0, 0);
		while(fgets(line, sizeof(line), f)) {
			if (sscanf(line, "hw.cpufrequency: %f", &freq_mhz) == 1) {
				bingo = true;
				break;
			}
		}
		if (bingo) 
		{
			fclose(f);	
			return (float)(freq_mhz);
		} 
		
	}

	cerr << "CPU: couldn't parse cpu freq, using fictitious freq of 2.6Ghz." << endl;
	return 0.0f;
#else
	FILE *f = fopen("/proc/cpuinfo", "r");
	if (f) {
		bool  bingo = false;
		float freq_mhz;
		char  line[256];
		while(fgets(line, sizeof(line), f)) {
			if (sscanf(line, "cpu MHz : %f", &freq_mhz) == 1) {
				bingo = true;
				break;
			}
		}
		if (bingo) 
		{
			fclose(f);
			return float64_t(freq_mhz) * 1e6;
		}
		
	}

	cerr << "CPU: couldn't parse cpu freq, using fictitious freq of \
			2Ghz." << endl;
	return 0.0f;
#endif
}