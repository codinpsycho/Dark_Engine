#include "Triangle.h"
#include "WorldTransform.h"
#include "Dark.h"
using namespace DarkEngine;

Triangle::Triangle(void) 
{
	m_showNormals = false;
	vbuffer = 0;
	for (int i = 0; i < 3; i++)
	{
		v[i].z = 0.5f;
		v[i].color1 = WHITE_COLOR(255);
		
	}
	//Create a new vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer( 3*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL)))
	{
		MESSAGE("Error creating Vertex Buffer");
	}
	else
		LoadVertexBuffer();



}
Triangle::Triangle(VERTEX v1, VERTEX v2, VERTEX v3) 
{
	m_showNormals = false;
	vbuffer = 0;
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
	
	//Create a new vertex Buffer
	if (FAILED(DarkEngine::Dark::Instance().GetRenderDevice()->CreateVertexBuffer( 3*sizeof(VERTEX), 0, FVF, D3DPOOL_MANAGED, &vbuffer, NULL)))
	{
		MESSAGE("Error creating Vertex Buffer");
	}
	else
		LoadVertexBuffer();



	
}

Triangle::~Triangle(void)
{
SAFE_RELEASE(vbuffer);
}

bool Triangle::LoadVertexBuffer()
{

	void *data = NULL; 
	vbuffer->Lock(0,0,(void**)&data,0);		//Locked 
	memcpy(data,v,sizeof(v));				//Loading
	vbuffer->Unlock();						//Done, unlock now

	return true;
}


bool Triangle::Update(float dt, LPDIRECT3DDEVICE9 device)
{
	
//	if(m_showNormals)	DrawNormals();
// 	if(FAILED(device->SetFVF(FVF)))
// 	{
// 		MESSAGE("FVF Failed");
// 		LOG("FVF Failed\n");
// 		return false;
// 	}
	if(FAILED(device->SetStreamSource(0, vbuffer, 0, sizeof(VERTEX))))
	{
		MESSAGE("Stream source set Failed");
		LOG.Write("Stream source set Failed\n");
		return false;
	}
	if(FAILED(device->SetVertexShaderConstantF(4,(float*)m_worldTransform->GetTransposedTransform(), 4)))
	{
		MESSAGE("Vertex Shader Constant set failed");
		LOG.Write("Vertex Shader Constant set failed\n");
		return false;
	}
	//device->SetTransform(D3DTS_WORLD, m_worldTransform->GetTransform() );
// 	if(m_material)
// 	EngineManager::Instance()->GetD3DDevice()->SetMaterial(m_material->GetD3DMaterial());
// 	EngineManager::Instance()->GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,1);

	return true;
}

bool Triangle::DrawGeometry(LPDIRECT3DDEVICE9 device)
{
	if(FAILED(device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,3,0,1)))
	{
		MESSAGE("Triangle Draw Failed");	
		LOG.Write("Triangle Draw Failed\n");
		return false;
	}
	return true;
}



