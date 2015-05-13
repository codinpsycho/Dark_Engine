#include "GraphicsStats.h"


GraphicsStats::GraphicsStats(void) 
{
	m_deltaTime = 0.0f;
	m_fps = 0.0f;
	m_timer.Start();
}

GraphicsStats::~GraphicsStats(void)
{
}

float GraphicsStats::GetDeltaTime()
{
	//Stop the timer
	m_timer.Stop();
	//Get time elapsed
	m_deltaTime = m_timer.GetDeltaTime();
	//Then start again for next round of update-render loop
	m_timer.Start();

	return m_deltaTime;
}

float GraphicsStats::GetFps()
{
	//Declare static so they are not allocated every frame
	static float tempDt = 0.0f;
	static float tempFps = 0.0f;
	//Increment the frame count
	++tempFps ;
	
	//If time exceeds 1.0f(1 sec), then we get our FPS
	if( (tempDt += m_deltaTime) > 1.0f)
	{
		tempDt = 0.0f;
		m_fps = tempFps;
		tempFps = 0.0f;
	}

	return tempFps;


}
