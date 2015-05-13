#pragma once

#include "Timer.h"
//#include "Text.h"

class GraphicsStats
{
public:
	GraphicsStats(void);
	virtual ~GraphicsStats(void);
	float GetDeltaTime();
	float GetFps();
	float MilliSecPerFrame();
private:
	//Text m_text;
	Timer m_timer;
	float m_deltaTime;
	float m_fps;

};
