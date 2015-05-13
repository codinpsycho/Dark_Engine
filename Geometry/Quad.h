#pragma once
#include "IGeometry.h"

class CLine;
class CTexture;
class CWorldTransform;

typedef enum  
{
	NO_BLENDING,
	COLOR_ADD,
	COLOR_MUL,
	ALPHA_ADD,
	ALPHA_MUL,
	BURNOUT,
	DARKEN,
} BLEND;


class Quad : public IGeometry
{

////////////////////////////////
public:
	Quad(void);
	Quad(float x,float  y, float width, float height);
	Quad(VERTEX *v);
	Quad(const Quad& quad_ );
	virtual ~Quad(void);
	void SetZ(float);
	bool Update(float dt, LPDIRECT3DDEVICE9 device);
	bool Release();
	bool DrawGeometry(LPDIRECT3DDEVICE9 device);
	D3DPRIMITIVETYPE GetPrimitiveType()		{ return D3DPT_TRIANGLESTRIP;	}
	int GetVertexCount()					{ return 4;						}
	int GetPrimitiveCount()					{ return 2;						}
	
// 	void ShowNormals();
// 	void SetDiffuseColor(DWORD color_, int index = -1);
// 	void SetSpecularColor(DWORD color_, int index = -1);
// 	bool SetTexture(CTexture*)	;
	void UpdateUVs(int index, float u_, float v_)			{ v[index].tu = u_, v[index].tv = v_; m_updateVertices = true;}
	VERTEX*	GetQuadVertices()								{ m_updateVertices = true; return v;}	
	//void SetBlend(BLEND);
	float GetDepth()										{ return depth;	}
	//Rect GetRect()										{ return Rect(WorldTransform()->GetTransform()->_41, WorldTransform()->GetTransform()->_42, width, height); }
	
////////////////////////////////
private:
	
	bool LoadVertexBuffer();
	bool LoadIndexBuffer();
	VERTEX v[4];
	CLine *lineX, *lineY, *lineZ;
	LPDIRECT3DVERTEXBUFFER9 vbuffer;
	LPDIRECT3DINDEXBUFFER9 ibuffer;
	void DrawNormals();
	bool m_showNormals;
	float width,height,depth;
	bool m_updateVertices;
	//CWorldTransform *m_worldTransform;
};
