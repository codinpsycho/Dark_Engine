#pragma once
#include "Direct3D.h"

//Forward declared
class CWorldTransform;

// Font alignment
enum FONTALIGNMENT { FA_LEFT, FA_CENTER, FA_RIGHT, FA_TOPRIGHT, FA_TOPLEFT, FA_BOTTOMRIGHT, FA_BOTTOMLEFT };


class Text
{
public:
	Text(void);
	virtual ~Text(void);
	int Render2D(int xPos, int yPos, int textBoxWidth,int textBoxHeight, DWORD color, char *text,...);
	int Render2D(char *text, int xPos, int yPos, int textBoxWidth,int textBoxHeight, DWORD color ,int count = -1, FONTALIGNMENT alignment = FA_LEFT);
	void Render3D(LPDIRECT3DDEVICE9 device);
	bool Create2DText(LPDIRECT3DDEVICE9, char* faceName,int size, int weight =100, bool bold = false, bool italic = false);
	bool Create3DText(LPDIRECT3DDEVICE9, char* text,int size, int weight =100, bool bold = false, bool italic = false);
	CWorldTransform& WorldTransform()	{ assert(m_worldTransform); return *m_worldTransform;	}
	
private:
	LPD3DXFONT m_text;
	CWorldTransform *m_worldTransform;
	LPD3DXMESH m_textMesh;	//For 3D text
};

