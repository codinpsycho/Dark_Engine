#pragma once
#include "IGeometry.h"



//Forward Declared classes
class CWorldTransform;

class Triangle : public IGeometry
{

public:
	bool Initialize();
	bool Update(float dt, LPDIRECT3DDEVICE9 device);
	bool Release(); 
	bool DrawGeometry(LPDIRECT3DDEVICE9 device);
	D3DPRIMITIVETYPE GetPrimitiveType()		{ return D3DPT_TRIANGLESTRIP;	}
	int GetVertexCount()					{ return 3;						}
	int GetPrimitiveCount()					{ return 1;						}
	void SetZ(float);
	Triangle(void);
	Triangle::Triangle(VERTEX v1, VERTEX v2, VERTEX v3);
	virtual ~Triangle(void);
	
	void ShowNormals();

protected:

	bool LoadVertexBuffer();

	void DrawNormals();
	bool m_showNormals;
	VERTEX v[3];
	LPDIRECT3DVERTEXBUFFER9 vbuffer;
	CWorldTransform *m_worldTransform;

};
