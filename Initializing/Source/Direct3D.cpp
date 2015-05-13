#include "Direct3D.h"
#include "DarkDefs.h"
#include "Log.h"



Direct3D::Direct3D(void)
{
	d3d = NULL;
	d3ddev = NULL;
	window  = new win32("Direct3D");

}

Direct3D::~Direct3D(void)
{
	SAFE_RELEASE(d3d);
	SAFE_RELEASE(d3ddev);
	SAFE_DELETE(window);
}

bool Direct3D::CreateRenderWindow(HINSTANCE instance, int xPos, int yPos, int width, int height)
{
	
	//If win32 window created successfully
	if(window->CreateWin32Window(instance, xPos, yPos, width, height))
	{
		Log::Instance()<<"Creating D3D pointer\n";
		//Create d3d mpointer
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!d3d)
		{
			MESSAGE("D3D initialization failed");
			return false;
		}
		
		d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display);


		
		//Build Presentation parameters
		MakePresentationParameters();
		//Now create the actual device 
		Log::Instance()<<"Creating D3D device\n";
		if(FAILED(CreateD3dDevice()))
		{
			Log::Instance()<<"D3D device creation failed\n";
			MESSAGE("D3D Device creation failed\n");
			return false;
		}

		//Set some basic render states
		SetRenderStates();
		
		//If everything is success, show the window and return
		window->DisplayWindow();

		return true;
	}	
	else
		return false;
	

}


void Direct3D::MakePresentationParameters()
{
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//Set basic properties
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
 	d3dpp.BackBufferHeight = window->GetHeight();
 	d3dpp.BackBufferWidth = window->GetWidth();
 	d3dpp.hDeviceWindow = window->GetHandle();
 	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	//Vertical Sync on
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//Vertical Sync off
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D32;

}


HRESULT Direct3D::CreateD3dDevice()
{
	DWORD vertex_processing = 0;
	if( m_devCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vertex_processing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vertex_processing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	
	return  d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->GetHandle(), vertex_processing, &d3dpp, &d3ddev);

	
}

void Direct3D::SetRenderStates()
{
	if(FAILED(d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW)))
		MESSAGE("Culling Mode Failed");
	if(FAILED(d3ddev->SetRenderState(D3DRS_ZENABLE, true)))
		MESSAGE("Zenable failed");
	if(FAILED(d3ddev->SetRenderState(D3DRS_LIGHTING, false)))
		MESSAGE("Lighning failed");
	if(FAILED(d3ddev->SetRenderState(D3DRS_NORMALIZENORMALS, true)))
		MESSAGE("Normalizing failed");
	if(FAILED(d3ddev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG)))
		MESSAGE("Phong Shading failed");
	if(FAILED(d3ddev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL)))
		MESSAGE("diffuse color from material");
	// 	if(FAILED(d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true)))
	// 		window->ShowMessage(L"Frame Buffer Blending enable failed ", L"Error");
	// 	if(FAILED(d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE)))
	// 		window->ShowMessage(L"Source color Blend", L"Error");
	// 	if(FAILED(d3ddev->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO)))
	// 		window->ShowMessage(L"Dest blend failed", L"Error");
	// 	if(FAILED(d3ddev->SetRenderState(D3DRS_SPECULARENABLE,true)))
	// 		window->ShowMessage(L"Dest blend failed", L"Error");


	// 	if(FAILED(d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE,D3DCMP_GREATEREQUAL)))
	// 		window->ShowMessage(L"Dest blend failed", L"Error");
	// 	if(FAILED(d3ddev->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATEREQUAL)))
	// 		window->ShowMessage(L"Dest blend failed", L"Error");
	// 	if(FAILED(d3ddev->SetRenderState(D3DRS_ALPHAREF,(DWORD)0x000000ff)))
	// 		window->ShowMessage(L"Dest blend failed", L"Error");
}