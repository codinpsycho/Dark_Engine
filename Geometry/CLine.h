#pragma once
#include "IGeometry.h"

//Forward Declared class
class CWorldTransform;

class CLine : public IGeometry
{
public:
	CLine(void);
	CLine( D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, DWORD color_);
	CLine( float x1, float y1, float z1, float x2, float y2, float z2, DWORD color_ = 0xffffffff );
	void SetColor(DWORD color_ );

	void SetZ(float);
	bool Initialize();
	bool Update(float dt, LPDIRECT3DDEVICE9 device);
	bool DrawGeometry(LPDIRECT3DDEVICE9 device); 
	bool Release();
	D3DPRIMITIVETYPE GetPrimitiveType()	{ return D3DPT_LINESTRIP;	}
	int GetVertexCount()				{ return 2;					}	
	int GetPrimitiveCount()				{ return 1;					}
	
	virtual ~CLine(void);
private:
	bool LoadVertexBuffer();

	VERTEX v[2];
	LPDIRECT3DVERTEXBUFFER9 vbuffer;

};
