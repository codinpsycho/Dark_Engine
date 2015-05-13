#include "DefaultDarkScene.h"
#include "Text.h"
#include "Dark.h"
#include "DarkDefs.h"
#include "RenderEntity.h"
#include "RenderProperty.h"
#include "EntityManager.h"
#include "Quad.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Camera.h"
#include "CInputManager.h"
#include "CLine.h"
#include "GraphicsManager.h"
#include "DarkSprite.h"
#include "DarkRect.h"
#include "DarkMesh.h"
using namespace DarkEngine;

//Creating an anonymous namespace for this scene only, wont be visible outside this .cpp
///So its not actually global/ but in a sort yes... :)
namespace
{
//Data
Text *text = 0;
RenderEntity *ish = 0;
Quad *q = 0;
CDarkMesh *mesh = 0;
CLine *x = 0, *y = 0, *z  = 0;
LPDIRECT3DVERTEXDECLARATION9 vertDecl = 0;


//Fucntions


}
void HandleCameraMovement();


CDefaultDarkScene::CDefaultDarkScene(void)
{
}

CDefaultDarkScene::~CDefaultDarkScene(void)
{

}

bool CDefaultDarkScene::Initialize()
{
	//initialize your Scene here
	text = new Text;
	//text->Create2DText(DarkEngine::Dark::Instance().GetRenderDevice(), "Verdana", 40);
	text->Create3DText(RENDER_DEVICE, "Ishkaran", 12);
	
	//Creating a render entity
	//1. you need a render property and a geometry
	//2. After that register your entity with the EntityManager
	ish = new RenderEntity;
	CRenderProperty prop("ish");	//Render Property
	
	q = new Quad(100,38,50,30);	//Geometry
	CDarkMesh& mesh = (CDarkMesh&)RESOURCE_MANAGER.GetResource(DRES_MESH, "cube.x");

	x = new CLine(1000,0,0,-1000,0,0,0xff000000);
	y = new CLine(0,1000,0,0,-1000,0,0x00ff0000);
	z = new CLine(0,0,1000,0,0,-1000,0x0000ff00);

	prop.AddTexture("..\\Data\\Textures\\nullTexture.png");
	prop.AddVertexShader("..\\Data\\Shaders\\ppl pixel.txt");
	prop.AddPixelShader("..\\Data\\Shaders\\ppl vertex.txt");
 	
	//Two main functions that defines how an entity will look
	ish->SetRenderProperty(prop);
	ish->SetGeometry(&mesh);

	ENTITY_MANAGER.Register(*ish);
	//ENTITY_MANAGER.Register(*ish);

	//Now Create a camera and set it as active Camera
	CCamera *camera = new CCamera();
	camera->Init();
	camera->SetPosition(0,100,-300);
	DARK.SetActiveCamera(camera);


// 	//Testing
// 	D3DVERTEXELEMENT9 decl[] = 
// 	{
// 		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,0 },
// 		{ 0, 12,D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
// 		{0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
// 		{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0  },
// // 		{0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
// // 		{0, 48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
// 		// 		{0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
// 		// 		{0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
// 
// 		D3DDECL_END()
// 	};
// 
// 	//Create vertex declaration
// 	if(FAILED(RENDER_DEVICE->CreateVertexDeclaration(decl,&vertDecl)))
// 		MESSAGE("Vertex Decl Failed");
// 
// 	if(FAILED(RENDER_DEVICE->SetVertexDeclaration(vertDecl)))
// 		MESSAGE("AGAIN FAILED");

 	
	return true;	
}


bool CDefaultDarkScene::Update(float dt)
{
	//Update your scene here
	HandleCameraMovement();
	ENTITY_MANAGER.UpdateEntites(dt);

	return true;
}

bool CDefaultDarkScene::Render()
{
	//Render your scene here
  	DarkRect rect(-100,100,500,500);
	GRAPHICS_MANAGER.ShowTexture(rect, "xhcfkjdsc");
	//1. Render all your entities by calling EntityManager().RenderEntities()
	//it will automatically do the batching depending on RenderProperties
	ENTITY_MANAGER.RenderEntities();
	GRAPHICS_MANAGER.ShowText(100,100,200,200,COLOR_ARGB(255,255,100,80), "Testing : %s", "Graphics Manager");
	GRAPHICS_MANAGER.ShowText(200,150,200,200,COLOR_ARGB(255,255,100,200), "Testing : %s", "DarkSprites");

	
	
	//Render lines
	//x->DrawGeometry(RENDER_DEVICE);
	//y->DrawGeometry(RENDER_DEVICE);
	//z->DrawGeometry(RENDER_DEVICE);
	text->Render3D(RENDER_DEVICE);
	return true;


}


bool CDefaultDarkScene::Release()
{
	//Release your scene resources here
	//Keep the heap clean and happy else it gets wild :)
	SAFE_DELETE(x);
	SAFE_DELETE(y);
	SAFE_DELETE(z);
	return true;
}

//Game Spcific Functions : 
void HandleCameraMovement()
{
	CCamera& tempCam = (CCamera&)DARK.GetCamera();

	if(INPUT_MANAGER.KeyDown(DIK_W))
		tempCam.MoveForward(10);
	
	if(INPUT_MANAGER.KeyDown(DIK_S))
		tempCam.MoveBackward(10);
	
	if(INPUT_MANAGER.KeyDown(DIK_A))
		tempCam.MoveLeft(10);
	
	if(INPUT_MANAGER.KeyDown(DIK_D))
		tempCam.MoveRight(10);

	if(INPUT_MANAGER.KeyDown(DIK_Q))
		tempCam.MoveUp(10);

	if(INPUT_MANAGER.KeyDown(DIK_E))
		tempCam.MoveDown(10);
}