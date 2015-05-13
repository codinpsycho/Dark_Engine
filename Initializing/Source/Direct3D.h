#ifndef _DIRECT_3D_H
#define _DIRECT_3D_H

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9anim.h>
#include "win32.h"
#include <io.h>
#include <assert.h>



#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//win32 Direct3D::window = 0;
class Direct3D
{
	LPDIRECT3D9 d3d;				//an interface to direct3d COM
	LPDIRECT3DDEVICE9 d3ddev;		//main interface to our graphic device
	D3DCAPS9 m_devCaps;				//to get devices capabilities
	D3DPRESENT_PARAMETERS d3dpp;	//Presentation parameters 
	D3DDISPLAYMODE display;
	win32 *window;					//For Creating window and windows functionality
	
	//Called through CreateRenderWindow()
	void MakePresentationParameters();
	void SetRenderStates();
	HRESULT CreateD3dDevice();

public:
	//manages all initialization, win32 window as well as directX initialization
	bool CreateRenderWindow(HINSTANCE instance, int xPos, int yPos, int width, int height);
	//Accessor functions
	const win32& GetWindow()	const			{ return *window; }
	LPDIRECT3D9 GetD3D()  const					{ return d3d;	 }
	LPDIRECT3DDEVICE9 GetD3DDevice()  const		{ return d3ddev; }

	Direct3D(void);
	~Direct3D(void);



};


/////////////////////////////////////////DECLARATIONS////////////////////////////////////////////////////////




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






//Our Custom FVF
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
struct CUSTOM_VERTEX
{
	float x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};


#define FVF ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL )
struct VERTEX 
{
	float x,y,z;
	DWORD color1;	//Diffuse color
	//DWORD color2;	//Specular color
	float tu,tv;	//Texture coordinates
	D3DXVECTOR3 Normal;
	
	VERTEX()
	{
		x = y = z = tu = tv = 0.0f;
		Normal.x = Normal.y = 0.0f, Normal.z = -1.0f;
		/*color2 =*/ color1 = WHITE_COLOR(255);

	}
	VERTEX(float x_, float y_, float z_, D3DXVECTOR3 normal_)
	{
		/*color2 =*/ color1 = WHITE_COLOR(255);
		x = x_, y = y_, z = z_, tu = tv = 0.0f;
		Normal = normal_;
	}
	VERTEX(float x_, float y_, float z_, D3DXVECTOR3 normal_, float tu_, float tv_)
	{
		/*color2 =*/ color1 = WHITE_COLOR(255);
		x = x_, y = y_, z = z_, tu = tu_, tv = tv_;
		Normal = normal_;
	}

	VERTEX(float x_, float y_, float z_, D3DXVECTOR3 normal_, DWORD color1_)
	{
		/*color2 =*/ color1 = color1_;
		x = x_, y = y_, z = z_,  tu = tv = 0.0f;
		Normal = normal_;
	}
	VERTEX(float x_, float y_, float z_, D3DXVECTOR3 normal_, float tu_, float tv_, DWORD color1_, DWORD color2_)
	{
		/*color2 = */color2_, color1 = color1_;
		x = x_, y = y_, z = z_, tu = tu_, tv = tv_,0.0f;
		Normal = normal_;
	}
		
};

#define FVF_LIT ( D3DFVF_XYZ | D3DFVF_DIFFUSE )
struct VERTEX_LIT
{
	float x,y,z;
	float nx,ny,nz;


	float tu,tv;	//Texture coordinates
};

//Function Prototypes
bool Render();
bool Init();
bool Release();
bool Update(float);





#define SetTextureColorStage( dev, i, arg1, op, arg2 )     \
	dev->SetTextureStageState( i, D3DMTSS_COLOROP, op);      \
	dev->SetTextureStageState( i, D3DMTSS_COLORARG1, arg1 ); \
	dev->SetTextureStageState( i, D3DMTSS_COLORARG2, arg2 );

#define SetTextureAlphaStage( dev, i, arg1, op, arg2 )     \
	dev->SetTextureStageState( i, D3DMTSS_ALPHAOP, op);      \
	dev->SetTextureStageState( i, D3DMTSS_ALPHARG1, arg1 );  \
	dev->SetTextureStageState( i  D3DMTSS_ALPHARG2, arg2 );





#endif