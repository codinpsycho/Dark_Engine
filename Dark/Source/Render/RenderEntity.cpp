#include "RenderEntity.h"
#include <assert.h>
#include "Dark.h"
#include "IGeometry.h"
#include "WorldTransform.h"
using namespace DarkEngine;


RenderEntity::RenderEntity(void)
{
	//Now initialize
	m_worldTransform = new CWorldTransform;
}

RenderEntity::~RenderEntity(void)
{
	SAFE_DELETE(m_worldTransform);
}



bool RenderEntity::Render()
{
	//make sure there is a geometry to draw
	assert(m_geometry);

	//Sets the World Transformation Matrix	
	if(FAILED(RENDER_DEVICE->SetVertexShaderConstantF(4,(float*)m_worldTransform->GetTransposedTransform(), 4)))
	{
		MESSAGE("Set Vertex Shader Constant Failed");	
		LOG.Write("Set Vertex Shader Constant in Quad\n");
		return false;
	}



	m_geometry->DrawGeometry(RENDER_DEVICE);
	return true;
}

bool RenderEntity::Update(float dt)
{
	m_geometry->Update(dt, RENDER_DEVICE);
	return true;
}

bool RenderEntity::Release()
{
	return true;
}
