//.....................................................
//		Dark Engine :: Sprite Class 
//		Coded by Ishkaran Singh
//		28/Apr/12
//		I Game hard, I Code Harder
//.....................................................

#ifndef SPRITE_H_
#define SPRITE_H_

//#include "Direct3D.h"
#include "RenderEntity.h"
#include "ResourceManager.h"
#include "DarkDefs.h"
#include "WorldTransform.h"

//Forward Declarations
class Quad;
class DarkRect;
class CTexture;

class CDarkSprite : RenderEntity
{
public:
	CDarkSprite(DarkRect& rect_, char *texture /* Path to texture*/ );
	virtual ~CDarkSprite(void);
	bool RenderSprite();
	void SetTransform(CWorldTransform& transform_);
	void SetTexture(char *path_)				{ m_texturePath = path_;	}	
	CTexture& GetTexture()						{ return (CTexture&)RESOURCE_MANAGER.GetResource(DRES_TEXTURE, m_texturePath);	}
	void SetPosition(D3DXVECTOR3 pos_)			{ WorldTransform().SetPositionAbs(pos_.x, pos_.y, pos_.z);						}		
	void Rotate(float x, float y, float z)		{ WorldTransform().SetRoatationAbs(x,y,z);										}
	void Tile(int x, int y);
	void ScrollX(float dir_, float speed_);
	void ScrollY(float dir_, float speed_);
	void ScaleTexture(float x_, float y_);			//Scale the texture while width and height remains same
	void FlipX();
	void FlipY();
	void SetTextureRect(DarkRect& rect_,  char *path);			//which part of texture to map to sprite		
	void SetTextureRect(float x_, float y_, float width_, float height_,  char *path);//which part of texture to map to sprite
	
private:
	Quad *m_quad;
	char *m_texturePath;
	
};

#endif