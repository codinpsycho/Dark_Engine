//Header FIle for all #defines/typedefs and global functions to be used in dark Engine
#include "Direct3D.h"
#include "Log.h"
#include <stdarg.h>
#include <vector>
//To get __LINE__ and __FILE__ in string buffer
#define LINE_AND_FILE(buff)	sprintf(buff, "%i \n %s", __LINE__, __FILE__)

//To show an message in message box along with __LINE and __FILE__
#define MESSAGE(text)	{	char buff[512];	 \
	sprintf_s(buff, 512, "%s\nLine : %i\nFile : %s",text,__LINE__,__FILE__); \
	MessageBox(NULL,(char*)buff,"Error",MB_ICONEXCLAMATION | MB_OK);	\
}

//#define DEBUG_MESSAGE(text)	{#ifdef _DEBUG	MESSAGE(text);	}
	


#define SAFE_RELEASE(ptr)	assert(ptr); ptr->Release()

#define SAFE_DELETE(ptr)	assert(ptr); delete ptr, ptr = 0

//To check if certain file exists or not
#define FILE_EXISTS(name) _access(name,0) != -1

//SOme memory related Defines
#define EqualDarkMemory(Destination,Source,Length) (!memcmp((Destination),(Source),(Length)))
#define MoveDarkMemory(Destination,Source,Length)	memmove((Destination),(Source),(Length))
#define CopyDarkMemory(Destination,Source,Length)	memcpy((Destination),(Source),(Length))
#define FillDarkMemory(Destination,Length,Fill)		memset((Destination),(Fill),(Length))
#define ClearDarkMemory(Destination,Length)			memset((Destination),0,(Length))


//COLOR will be used throughout my framework to represent any color
typedef DWORD COLOR;
#define  COLOR_ARGB(a,r,g,b)((COLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

typedef D3DCOLORVALUE COLORVALUE;
#define COLORVALUE_RGBA(r,g,b,a) D3DXCOLOR(r,g,b,a)
#define COLOR_VALUE_RGBA(r,g,b,a) D3DXCOLOR((float)(r/255.0f),(float)(g/255.0f),(float)(b/255.0f),(float)(a/255.0f))

//For predefined color values
#define WHITE_COLOR(x) D3DXCOLOR((float)x/255.0f,(float)x/255.0f,(float)x/255.0f,1.0f)
#define RED_COLOR(x) D3DXCOLOR((float)x/255.0f,0.0f,0.0f,1.0f)
#define BLUE_COLOR(x) D3DXCOLOR(0.0f,0.0f,(float)x/255.0f,1.0f)
#define GREEN_COLOR(x) D3DXCOLOR(0.0f,(float)x/255.0f,0.0f,1.0f)


//EXTERN FUNCTIONS present in DarkFunctions.cpp
template<class T>
void DeleteVector(std::vector<T> &list);

template<class T>
void ReleaseVector(std::vector<T> &list);
void OutputString(char *format_, ...);

//Defs of Common  required Instances
#define ENTITY_MANAGER DarkEngine::EntityManager::Instance()
#define SCENE_MANAGER DarkEngine::SceneManager::Instance()
#define RESOURCE_MANAGER DarkEngine::ResourceManager::Instance()
#define RENDER_DEVICE DarkEngine::Dark::Instance().GetRenderDevice()	//Return a pointer
#define RENDER_WINDOW DarkEngine::Dark::Instance().GetRenderWindow()
#define INPUT_MANAGER DarkEngine::Dark::Instance().GetInputHandler()
#define LOG	Log::Instance()
#define GRAPHICS_MANAGER DarkEngine::CGraphicsManager::Instance()
#define DARK DarkEngine::Dark::Instance()		



//Names of resources used to remove any mistakes with text
#define DRES_TEXTURE			"texture"
#define DRES_VERTEXSHADER		"vertex shader"
#define DRES_PIXELSHADER		"pixel shader"
#define DRES_MESH				"mesh"
#define DRES_SOUND				"sound"


//Suppressing warnings
#pragma warning(disable : 4150)		//Destructor called on Incomplete type

//Defines for Sprites sorting and other things
#define BACK_TO_FRONT_SORT	D3DXSPRITE_SORT_DEPTH_BACKTOFRONT
#define FRONT_TO_BACK_SORT	D3DXSPRITE_SORT_DEPTH_FRONTTOBACK
#define BILLBOARD_SPRITE	D3DXSPRITE_BILLBOARD
#define TEXTURE_SORT		D3DXSPRITE_SORT_TEXTURE