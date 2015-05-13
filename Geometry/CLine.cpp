#include "CLine.h"
#include "Dark.h"
#include "WorldTransform.h"
using namespace DarkEngine;

CLine::CLine(void) 
{
	for (int i = 0; i < 2; i++)
	{
		v[i].z = 0.5f;
		//v[i].color = 0xffffffff;

	}

	v[0].Normal.x = 0, v[0].Normal.y = 1, v[0].Normal.z = 0;
	v[1].Normal.x = 0, v[1].Normal.y = 1, v[1].Normal.z = 0;
	
	//Create a new vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer( 2*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL)))
	{
		MESSAGE("Error creating Vertex Buffer");
	}
	else
		LoadVertexBuffer();


	
}

CLine::CLine(D3DXVECTOR3* pos1_, D3DXVECTOR3* pos2_ , DWORD color_) 
{
	for (int i = 0; i < 2; i++)
	{
		v[i].z = 0.5f;
		//v[i].color = color_;
	}

	v[0].Normal.x = 0, v[0].Normal.y = 1, v[0].Normal.z = 0;
	v[1].Normal.x = 0, v[1].Normal.y = 1, v[1].Normal.z = 0;
	vbuffer = 0;
	v[0].x = pos1_->x;
	v[0].y = pos1_->y;
	v[0].x = pos1_->z;
	v[1].x = pos1_->x;
	v[1].y = pos1_->y;
	v[1].z = pos1_->z;
	
	//Create a new vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer( 2*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL)))
	{
		MESSAGE("Error creating Vertex Buffer");
	}
	else
		LoadVertexBuffer();


	

}

CLine::CLine(float x1_, float y1_, float z1_, float x2_, float y2_, float z2_ , DWORD color_) 
{
	for (int i = 0; i < 2; i++)
	{
		v[i].z = 0.5f;
		v[i].color1 = COLOR_ARGB(255,255,255,255);
	}
	v[0].x = x1_;
	v[0].y = y1_;
	v[0].z = z1_;
	v[1].x = x2_;
	v[1].y = y2_;
	v[1].z = z2_;

	v[0].Normal.x = 0, v[0].Normal.y = 0, v[0].Normal.z = -1;
	v[1].Normal.x = 0, v[1].Normal.y = 0, v[1].Normal.z = -1;

	//Create a new vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer( 2*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL)))
	{
		MESSAGE("Error creating Vertex Buffer");
	}
	else
		LoadVertexBuffer();


	
}

CLine::~CLine(void)
{
	SAFE_RELEASE(vbuffer);
}

bool CLine::LoadVertexBuffer()
{
	
	void *data = NULL; 
	vbuffer->Lock(0,0,(void**)&data,0);		//Locked 
	memcpy(data,v,sizeof(v));				//Loading
	vbuffer->Unlock();						//Done, unlock now

	return true;
}



bool CLine::Update(float dt, LPDIRECT3DDEVICE9 device)
{
	
	
	
	return true;

}

//Actual drawing is done here
bool CLine::DrawGeometry(LPDIRECT3DDEVICE9 device)
{
	if(FAILED(device->SetStreamSource(0,vbuffer,0,sizeof(VERTEX))))
	{
		MESSAGE("Set Stream Source Failed");	
		LOG.Write("Stream source failed in CLine\n");
		return false;
	}

	if (FAILED(device->DrawIndexedPrimitive(D3DPT_LINESTRIP,0,0,2,0,1)))
	{

		MESSAGE("Line Draw Failed");	
		LOG.Write("Line Draw Failed\n");
		return false;
	}
	return true;
}


void CLine::SetColor(DWORD color_ )
{
	//v[0].color = color_;
	//v[1].color = color_;
}

