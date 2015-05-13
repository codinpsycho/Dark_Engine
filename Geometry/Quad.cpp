#include "Quad.h"
#include "WorldTransform.h"
#include "Dark.h"
#include "Texture.h"
#include "ResourceManager.h"
using namespace DarkEngine;



Quad::Quad(void) 
{
	m_updateVertices = false;
	m_showNormals = false;
	
	for (int i = 0; i < 3; i++)
	{
		v[i].z = 0.5f;
		v[i].color1 = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		
	}

	depth = 1.0f;

	v[0].Normal.x = 0, v[0].Normal.y = 1, v[0].Normal.z = 0;
	v[1].Normal.x = 0, v[1].Normal.y = 1, v[1].Normal.z = 0;
	v[2].Normal.x = 0, v[2].Normal.y = 1, v[2].Normal.z = 0;
	v[3].Normal.x = 0, v[3].Normal.y = 1, v[3].Normal.z = 0;
	//Set default Textures UV's
	v[0].tu = 0, v[0].tv = 0;
	v[1].tu = 1, v[1].tv = 0;
	v[2].tu = 1, v[2].tv = 1;
	v[3].tu = 0; v[3].tv = 1;

	//Create Vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer(4*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL )))
	{
		MESSAGE("Error creating Vertex Buffer");		
	}

	if(LoadVertexBuffer())
	{
		//Now create the Index Buffer
		if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateIndexBuffer( 4*sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ibuffer, NULL )))
		{
			MESSAGE( "Error creating Index Buffer");	
		}
		LoadIndexBuffer();
	}
}


Quad::Quad(VERTEX *v_)
{
	m_updateVertices = false;
	m_showNormals = false;
 
	for (int i = 0; i < 3; i++)
	{
		v[i].z = 0.5f;
		v[i].color1 = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

	}
	depth = 1.0f;

	v[0] = v_[0];
	v[1] = v_[1];
	v[2] = v_[2];
	v[3] = v_[3];
	
	v[0].Normal.x = 0, v[0].Normal.y = 1, v[0].Normal.z = 0;
	v[1].Normal.x = 0, v[1].Normal.y = 1, v[1].Normal.z = 0;
	v[2].Normal.x = 0, v[2].Normal.y = 1, v[2].Normal.z = 0;
	v[3].Normal.x = 0, v[3].Normal.y = 1, v[3].Normal.z = 0;
	//Maps Textures
	v[0].tu = 0, v[0].tv = 0;
	v[1].tu = 1, v[1].tv = 0;
	v[2].tu = 1, v[2].tv = 1;
	v[3].tu = 0; v[3].tv = 1;

	//Create Vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer(4*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL )))
	{
		MESSAGE("Error creating Vertex Buffer");		
	}

	if(LoadVertexBuffer())
	{
		//Now create the Index Buffer
		if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateIndexBuffer( 4*sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ibuffer, NULL )))
		{
			MESSAGE( "Error creating Index Buffer");	
		}
		LoadIndexBuffer();
	}
}


Quad::Quad(const Quad& quad_ )
{
	
}


Quad::Quad( float _x, float _y, float  _width, float _height ) 
{
	
	m_showNormals = false;
	
	for (int i = 0; i < 4; i++)
	{
		v[i].z = 0.5f;
		v[i].color1 = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		
		
	}
	width = _width, height = _height;
	depth = 1.0f;
	v[0].x = _x;
	v[0].y = _y;
	v[1].x = _x + width;
	v[1].y = _y;
	v[2].x = _x + width;
	v[2].y = _y - height;
	v[3].x = _x;
	v[3].y = _y - height;
	v[0].Normal.x = 0, v[0].Normal.y = 0, v[0].Normal.z = -1;
	v[1].Normal.x = 0, v[1].Normal.y = 0, v[1].Normal.z = -1;
	v[2].Normal.x = 0, v[2].Normal.y = 0, v[2].Normal.z = -1;
	v[3].Normal.x = 0, v[3].Normal.y = 0, v[3].Normal.z = -1;
	//Maps Textures
	v[0].tu = 0, v[0].tv = 0;
	v[1].tu = 1, v[1].tv = 0;
	v[2].tu = 1, v[2].tv = 1;
	v[3].tu = 0; v[3].tv = 1;
	
	//Create Vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer(4*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL )))
	{
		MESSAGE("Error creating Vertex Buffer");		
	}

	if(LoadVertexBuffer())
	{
		//Now create the Index Buffer
		if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateIndexBuffer( 6*sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ibuffer, NULL )))
		{
			MESSAGE( "Error creating Index Buffer");	
		}
		LoadIndexBuffer();
	}
	
}

Quad::~Quad(void)
{
	SAFE_RELEASE(vbuffer);
	SAFE_RELEASE(ibuffer);	
}

bool Quad::LoadVertexBuffer()
{
	void *data = 0;
	vbuffer->Lock(0,0,(void**)&data, 0);	//Locked
	memcpy( data,v,sizeof(v) );				//loaded
	vbuffer->Unlock();						//Release

	m_updateVertices = false;

	return true;
}

bool Quad::LoadIndexBuffer()
{

	//Now create an array of indices
	short indices[] = {  0,1,2,3,0,2 };

	void *idata = 0;
	ibuffer->Lock(0,0, (void**)&idata, 0);		//Locked
	memcpy(idata, indices, sizeof(indices) );	//loaded
	ibuffer->Unlock();							//Release
	
	return true;

}

bool Quad::Update(float dt, LPDIRECT3DDEVICE9 device)
{
	//Physics based Update here
	return true;
}

bool Quad::DrawGeometry(LPDIRECT3DDEVICE9 device)
{
// 	if (FAILED(device->SetFVF(FVF)))
// 	{
// 		MESSAGE("Set FVF Failed");	
// 		LOG("Set FVF Failed in Quad\n");
// 		return false;
// 	}

	if(m_updateVertices)
		LoadVertexBuffer();

	if (FAILED(device->SetStreamSource(0, vbuffer,0, sizeof(VERTEX) )))
	{
		MESSAGE("Set Stream Source Failed");	
		LOG.Write("Stream source failed in Quad\n");
		return false;
	}
	if (FAILED(device->SetIndices( ibuffer )))
	{
		MESSAGE("Set Indices Failed");	
		LOG.Write("Set Indices Failed in Quad");
		return false;
	}
	if(FAILED(device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2)))
	{
		MESSAGE("Triangle Draw Failed");	
		LOG.Write("Triangle Draw Failed\n");
		return false;
	}
	
	return true;
}



// 
// void Quad::SetDiffuseColor(DWORD color_, int index )
// {
// 	switch (index)
// 	{
// 	case -1 :
// 		v[0].color1 = color_;
// 		v[1].color1 = color_;
// 		v[2].color1 = color_;
// 		v[3].color1 = color_;
// 		break;
// 	}
// 	v[index].color1 = color_;
// 
// 	LoadVertexBuffer();
// 
// }


// void Quad::SetSpecularColor(DWORD color_, int index )
// {
// 	switch (index)
// 	{
// 	case -1 :
// // 		v[0].color2 = color_;
// // 		v[1].color2 = color_;
// // 		v[2].color2 = color_;
// // 		v[3].color2 = color_;
// 		break;
// 	}
// 	//v[index].color2 = color_;
// 
// }
// 

// void Quad::DrawNormals()
// {
// 
// 	lineZ->WorldTransform()->SetWorldTransform(this->WorldTransform());
// 	lineY->WorldTransform()->SetWorldTransform(this->WorldTransform());
// 	lineX->WorldTransform()->SetWorldTransform(this->WorldTransform());
// 
// }

// void Quad::ShowNormals()
// {
// 	for ( int i = 0; i < 4; i++ )
// 	{
// 		D3DXVec3Normalize(&v[i].Normal,&v[i].Normal);
// 	}
// 
// 
// 	lineX = new CLine(width/2,height/2,depth/2,v[0].Normal.x*10.0f,height/2,depth/2);
// 	lineX->Initialize();
// 	lineY = new CLine(width/2,height/2,depth/2,width/2,v[0].Normal.y*10.0f,depth/2);
// 	lineY->Initialize();
// 	lineZ = new CLine(width/2,height/2,depth/2,width/2,height/2,v[0].Normal.z*20.0f);
// 	lineZ->Initialize();
// 
// 	lineX->Material()->SetDiffuse(COLORVALUE_RGBA(0.0f,0.0f,0.0f,0.0f));
// 	lineY->Material()->SetDiffuse(COLORVALUE_RGBA(0.0f,0.0f,0.0f,0.0f));
// 	lineZ->Material()->SetDiffuse(COLORVALUE_RGBA(0.0f,0.0f,0.0f,0.0f));
// 
// 	m_showNormals = true;
// }
// 
// void Quad::SetBlend(BLEND blend)
// {
// 	switch (blend)
// 	{
// 	case NO_BLENDING :
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE)))
// 			message(L"No Blending Failed","ERROR");
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO)))
// 			message(L"No Blending Failed","ERROR");
// 		break;
// 	
// 
// 	case COLOR_ADD	:
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR)))
// 			message(L"No Blending Failed","ERROR");
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR)))
// 			message(L"No Blending Failed","ERROR");
// 		break;
// 
// 	case COLOR_MUL	:
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR)))
// 			message(L"No Blending Failed","ERROR");
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR)))
// 			message(L"No Blending Failed","ERROR");
// 		break;
// 
// 	case ALPHA_ADD :
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA)))
// 			message(L"No Blending Failed","ERROR");
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA)))
// 			message(L"No Blending Failed","ERROR");
// 		break;
// 
// 	case ALPHA_MUL :
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR)))
// 			message(L"No Blending Failed","ERROR");
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA)))
// 			message(L"No Blending Failed","ERROR");
// 		break;
// 
// 	case BURNOUT  :
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE)))
// 			message(L"No Blending Failed","ERROR");
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE)))
// 			message(L"No Blending Failed","ERROR");
// 		break;
// 	case DARKEN	  :
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR)))
// 			message(L"No Blending Failed","ERROR");
// 		if (FAILED(EngineManager::Instance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR)))
// 			message(L"No Blending Failed","ERROR");
// 		break;
// 	}
// }
