#pragma once

//Forward declaration
class CRenderProperty;
class IGeometry;

class IEntity
{
public:

	IEntity(void)
	{
	}

	virtual ~IEntity(void)
	{
	}
	
	virtual bool Update(float dt) = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;

};
