#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

enum eDEVICE { KEYBOARD, MOUSE };

class CInputManager
{
public:
	bool KeyDown(char key_)					{ return m_keyboardState[key_] & 0x80 ? true : false; }
	bool KeyUp(char key_)					{ return m_keyboardState[key_] & 0x80 ? false : true; }
	bool MouseButtonDown(int button_)		{ return m_mouseState.rgbButtons[button_] & 0x80 ?  true : false; }			
	void Update();
	void Init();
	long GetCursorXPosition()				{ LPPOINT p = 0; GetCursorPos(p); return p->x;	}	
	long GetCursorYPosition()				{ LPPOINT p = 0; GetCursorPos(p); return p->y;	}
	POINT* GetCursorPosition()				{ LPPOINT p = 0; GetCursorPos(p); return p;	    }
	long MouseDx()							{	return m_mouseState.lX;		}
	long MouseDy()							{	return m_mouseState.lY;		}
	long MouseDz()							{   return m_mouseState.lZ;		}
	CInputManager(void);
	virtual ~CInputManager(void);
private:
	LPDIRECTINPUT8			m_dInput;					//Our Interface to DirectInput
	LPDIRECTINPUTDEVICE8	m_keyboard;					//Our interface to a keyboard
	char					m_keyboardState[256];		//Data format for keyboard
	LPDIRECTINPUTDEVICE8	m_mouse;					//Our interface to mouse
	DIMOUSESTATE2			m_mouseState;				//Data format for our mouse can support 8 buttons
		
	bool CheckDeviceStatus(eDEVICE device_);			//Checks for Lost device
	void PollKeyboard();								//Handles keyboard 
	void PollMouse();									//Handles Mouse
	float m_x, m_y;										//Mouses current X,Y coordinates
};

#endif