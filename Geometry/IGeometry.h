#pragma once
#include "Direct3D.h"

class IGeometry
{
public:
	virtual bool Update(float dt, LPDIRECT3DDEVICE9 device) = 0;	
	virtual D3DPRIMITIVETYPE GetPrimitiveType()		{ return D3DPT_TRIANGLESTRIP;	}	//This should be the default primitive type	
 	virtual int GetVertexCount() = 0;
 	//virtual int GetPrimitiveCount()= 0;
	virtual int GetGeometryCount()					{ return 1;	}	//default only 1 geometry, should be overridden in case of a mesh 			
	virtual bool DrawGeometry(LPDIRECT3DDEVICE9 device) = 0;
	IGeometry(void)	{}
	virtual ~IGeometry(void)	{}
};

