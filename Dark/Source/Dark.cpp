#include "Dark.h"
#include "Log.h"
#include <stdio.h>
#include "DarkDefs.h"
#include "GraphicsStats.h"
#include "SceneManager.h"
#include "DefaultDarkScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ICamera.h"
#include "CInputManager.h"
#include "DarkMesh.h"
using namespace DarkEngine; 

Dark::~Dark(void)
{
	//Nothing here

}

bool Dark::Initialize(HINSTANCE instance_, int xPos_, int yPos_, int width_, int height_)
{
	//First maintain a log file
	Log::Instance().AttachFile("Log.txt");
	Log::Instance()<<"Starting Initialization\n";

	//Initializes other managers and subsystems
	m_Renderer = new Direct3D;

	if(m_Renderer->CreateRenderWindow(instance_, xPos_, yPos_, width_, height_))
	{
		Log::Instance()<<"Render Window Created\n";
		/*//If this succeeds, init other systems	*/
		//Init here
		Log::Instance()<<"Initializing Graphics Stats for Delta Time and FPS\n";
		m_stats = new GraphicsStats;
		
		LOG.Write("Initializing Input");
		m_inputHandler = new CInputManager;
		m_inputHandler->Init();			//Use Xinput  for X360 controller
		//Register some default resources with the resource manager, before Hooking a scene
		RegisterResources();
		LoadDefaultResources();

		//Hook a default Scene 
		Log::Instance()<<"Hooking a default Scene\n";
		DarkEngine::SceneManager::Instance().RegisterScene("Default", new CDefaultDarkScene);
		DarkEngine::SceneManager::Instance().SetCurrentScene("Default");
		
	}
	else
	{
		MESSAGE("Render window Failed");
		//Make an entry into Log
		Log::Instance()<<"Render window Failed\n";

		//Since the window isn't created nothing else will work
		return false;
	}
	
	

	Log::Instance()<<"Initializing Complete\n.\n.\n.\n.\n.\n";
	return true;
}


void Dark::RegisterResources()
{	
	if(!(RESOURCE_MANAGER.RegisterResource(DRES_TEXTURE, new CTextureCreator)))
		LOG.Write("Registering Resource : Texture FAILED");
	
	if(!(RESOURCE_MANAGER.RegisterResource(DRES_MESH, new CMeshLoader)))
		LOG.Write("Registering Resource : Mesh FAILED");

	if((!RESOURCE_MANAGER.RegisterResource(DRES_VERTEXSHADER, new CVertexShaderCreator)))
		LOG.Write("Registering Resource : Vertex Shader FAILED");
	
	if((!RESOURCE_MANAGER.RegisterResource(DRES_PIXELSHADER, new CPixelShaderCreator)))
		LOG.Write("Registering Resource : Pixel Shader FAILED");
	
	//Any more resources you may want...
}

void Dark::LoadDefaultResources()
{
	//Create some null resources to return if resource not found
	RESOURCE_MANAGER.CreateResource(DRES_TEXTURE, TextureHeader("..\\Data\\Textures\\nullTexture.png"));
	RESOURCE_MANAGER.CreateResource(DRES_MESH, MeshHeader("..\\Data\\Meshes\\Cube.x"));


	//Load Default Shaders, might be possible that user doesnt know how to write shaders 
	RESOURCE_MANAGER.CreateResource(DRES_VERTEXSHADER, IHeader("..\\Data\\Shaders\\ppl vertex.txt"));	
	RESOURCE_MANAGER.CreateResource(DRES_PIXELSHADER, IHeader("..\\Data\\Shaders\\ppl pixel.txt"));

}

//Main Functions which starts the Game loop and updates everything
void Dark::PowerStart()
{
	LOG.Write("Powering up the Engine\n");
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );

	while (1)
	{
		while(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			PostQuitMessage(0);
			break;
		} 
		else
		{
			
			//Check if graphic card is still with us
			HRESULT result = m_Renderer->GetD3DDevice()->TestCooperativeLevel();
			if (SUCCEEDED(result)) 
			{
				//Get Delta Time
				float dt = m_stats->GetDeltaTime();
				float fps = m_stats->GetFps();
				//Advance you Game here
				//Update your Game
				Update(dt);
				//Render your Game
				Render(WHITE_COLOR(255));
			}
			else
			{
				MESSAGE("Device Lost");
				
			}

		}

	}
}

//Close all sub-systems and prevent memory Leaks
bool Dark::ShutDown()
{
	Log::Instance()<<"Shutting Down Engine\n";
	//Delete pointers
	SAFE_DELETE(m_Renderer);
	SAFE_DELETE(m_stats);
	SAFE_DELETE(m_inputHandler);

	return true;
}


void Dark::OnLostDevice()
{
	//Code here for device lost condition
}


bool Dark::Update(float dt)
{	
	//All Your engine support system update goes here
	m_inputHandler->Update();				//Handles keyboard and mouse input, for now
	m_defaultCamera->Update(RENDER_DEVICE);	//Update the Camera, sets the View and Projection Matrix
	SCENE_MANAGER.Update(dt);				//Calls Current scenes Update()
	
	return true;
}

bool Dark::Render(COLOR color)
{
	//Do all your Rendering Here
	Begin(color);
	
	//Display Stats
#ifdef DEBUG_STATS

#endif


	//Rendering here
	//Render your current scene
	SCENE_MANAGER.Render();


	End();
	//if everything went well
	return true;

}

bool Dark::Begin(COLOR color)
{	
	//Clear your render targets and z-buffer
	if(SUCCEEDED(m_Renderer->GetD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0 )))
	//Let the show begin, it tells the graphic card, to stay away from back buffer, and locks it
		return SUCCEEDED(m_Renderer->GetD3DDevice()->BeginScene());
	//if anything goes wrong
	return false;

}

bool Dark::End()
{
	//Ok we are done with rendering
	if(SUCCEEDED(m_Renderer->GetD3DDevice()->EndScene()))
		//Now  present the scene to front buffer(actually it just switches the pointer to back and front buffer)
		return SUCCEEDED(m_Renderer->GetD3DDevice()->Present(NULL, NULL, NULL, NULL));
	//if anything goes wrong
	return false;
}