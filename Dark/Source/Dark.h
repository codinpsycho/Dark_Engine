#pragma once
#include "DarkDefs.h"

//Forward declared classes
class GraphicsStats;
class ICamera;
class CInputManager;


namespace DarkEngine
{
	class Dark
	{
	public:
		//Only Single Instance with local static object
		static Dark& Instance()
		{
			static Dark obj;
			return obj;
		}
		//Initialize required subsystems
		bool Initialize(HINSTANCE instance, int xPos, int yPos, int width, int height);
		//Power Start the Engine, enter the main game loop
		void PowerStart();
		//Close all Subsystems
		bool ShutDown();
		

		bool Begin(COLOR color);	//Begins rendering
		bool End();		//ends rendering		
		////////////////////////////
		//Accessor functions
		LPDIRECT3DDEVICE9 GetRenderDevice() const	{ return m_Renderer->GetD3DDevice();	}
		win32 GetRenderWindow()				const	{ return m_Renderer->GetWindow();		}
		LPDIRECT3D9	GetRenderer()			const	{ return m_Renderer->GetD3D();			}
		ICamera& GetCamera()				const	{ return *m_defaultCamera;				}
		void SetActiveCamera(ICamera *camera_)		{ m_defaultCamera = camera_;			}
		CInputManager& GetInputHandler()	const	{ return *m_inputHandler;				}
		//void SetInputHandler();	To be extended/improved later
		/////////////////////////////
		void OnLostDevice();
		virtual ~Dark(void);
	private:
		//Functions called from within the member functions
		void LoadDefaultResources();
		void RegisterResources();
		bool Update(float dt);
		bool Render(COLOR color);
		//Constructors
		Dark(void)	{}
		Dark(const Dark& rhs);
		Dark operator= (Dark& rhs);

		//Private Members
		Direct3D *m_Renderer;
		GraphicsStats *m_stats;
		ICamera *m_defaultCamera;
		CInputManager *m_inputHandler;

	};


}
