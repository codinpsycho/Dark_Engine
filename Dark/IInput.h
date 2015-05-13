#pragma once

class IInput
{
public:

	IInput(void)
	{
	}

	virtual ~IInput(void)
	{
	}

	virtual bool KeyDown() = 0;
	virtual bool KeyUp() = 0;
	

};
