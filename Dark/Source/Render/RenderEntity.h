#pragma once
#include "IEntity.h"
#include <assert.h>
#include "RenderProperty.h"

//Forward declarations
class CWorldTransform;
class IGeometry;


class RenderEntity : public IEntity
{
public:
	RenderEntity(void);
	virtual ~RenderEntity(void);
	bool Render();
	bool Update(float dt);
	bool Release();
	//Accessor functions
	virtual void SetGeometry(IGeometry* geometry)	{ m_geometry = geometry;	}
	virtual void SetRenderProperty(CRenderProperty&  renderProperty)	{ m_renderProperty = renderProperty;	}
	CRenderProperty& GetRenderProprety()			{	return m_renderProperty;								}
	IGeometry& GetGeometry()	const				{	assert(m_geometry);			return *m_geometry;			} 
	CWorldTransform& WorldTransform() const			{	assert(m_worldTransform);	return  *m_worldTransform;	}
private:

	CWorldTransform *m_worldTransform;			//Position and orientation in world space
	IGeometry *m_geometry;
	CRenderProperty m_renderProperty;

};
