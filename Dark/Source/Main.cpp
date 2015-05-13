#include "Dark.h"
#include "Text.h"
using namespace DarkEngine;

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	//Initializing
	if(DarkEngine::Dark::Instance().Initialize(hInstance, 0,0,0,0))
	{
		//Testing
		
		//Enter the Main Game Loop
		DarkEngine::Dark::Instance().PowerStart();
		//Shuting Down
		DarkEngine::Dark::Instance().ShutDown();
	}
	
	
	
	
	return 0;
}