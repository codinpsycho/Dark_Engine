#include "CInputManager.h"
#include "Dark.h"
using namespace DarkEngine;

CInputManager::CInputManager(void)
{
	m_x = m_y = 0.0f;
	m_dInput=NULL;
	m_keyboard=NULL;
	m_mouse=NULL;
	memset(m_keyboardState,'0',sizeof(m_keyboardState));

}

void CInputManager::Init()
{
	//Create the input device
	DirectInput8Create( RENDER_WINDOW.GetInstance(),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_dInput,NULL);

	m_dInput->Initialize(RENDER_WINDOW.GetInstance(),DIRECTINPUT_VERSION);
	//Use m_dInput to create keyboard 
	if(FAILED(m_dInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, 0 )))
		LOG.Write("Cannot Create Keybord Device");
	//Set Data Format
	if(FAILED(m_keyboard->SetDataFormat( &c_dfDIKeyboard)))
		LOG.Write("Cannot Create Keybord Device");
	//Set Cooperative Level
	if(FAILED(m_keyboard->SetCooperativeLevel( RENDER_WINDOW.GetHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		LOG.Write("Cannot Create Keybord Device");
	//Acquire Keyboard
	HRESULT hr;
	while(FAILED(hr = m_keyboard->Acquire()));
	 
	if(FAILED(hr))
		LOG.Write("Cannot Create Keybord Device");

	//Use m_dInput to create mouse
	if(FAILED(m_dInput->CreateDevice(GUID_SysMouse, &m_mouse, 0 )))
		LOG.Write("Cannot Create mouse Device");
	//Set mouse data format
	if(FAILED(m_mouse->SetDataFormat( &c_dfDIMouse2 )))
		LOG.Write("Cannot Create mouse Device");
#ifdef EXCLUSIVE_MOUSE
	//Set cooperative level
	if(FAILED(m_mouse->SetCooperativeLevel(RENDER_WINDOW.GetHandle(), DISCL_FOREGROUND | DISCL_EXCLUSIVE )))
		LOG.Write("Cannot Create mouse Device");
#elif defined(NONEXCLUSIVE_NOUSE)
	//Set cooperative level
	if(FAILED(m_mouse->SetCooperativeLevel(RENDER_WINDOW.GetHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE )))
		LOG.Write("Cannot Create mouse Device");
#endif
	
	//Acquire device
	while(FAILED(hr = m_mouse->Acquire()));

	if(FAILED(hr))
		LOG.Write("Cannot Acquire Mouse Device");



}

CInputManager::~CInputManager(void)
{
	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	if(m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}
	if (m_dInput)
	{
		m_dInput->Release();
		m_dInput = 0;
	}

}


void CInputManager::Update()
{
	if (m_keyboard)
		PollKeyboard();

	if(m_mouse)
		PollMouse();
}

void CInputManager::PollKeyboard()
{
	//1 . Check for lost device, if device lost , acquire again
	if (!CheckDeviceStatus(KEYBOARD))
	{
		ZeroMemory(m_keyboardState, sizeof(m_keyboardState));
		m_keyboard->Acquire();
	}

}
void CInputManager::PollMouse()
{
	//1 . Check for lost device, if device lost , acquire again
	if (!CheckDeviceStatus(MOUSE))
	{
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));
		m_mouse->Acquire();
	}

}


bool CInputManager::CheckDeviceStatus(eDEVICE device_)
{
	switch (device_)
	{
	case KEYBOARD :
		if(FAILED(m_keyboard->GetDeviceState(sizeof(m_keyboardState),(LPVOID)&m_keyboardState)))
			return false;
		break;
	case MOUSE:
		if(FAILED(m_mouse->GetDeviceState(sizeof(m_mouseState),&m_mouseState)))
			return false;
		break;
	}
	return true;
}

