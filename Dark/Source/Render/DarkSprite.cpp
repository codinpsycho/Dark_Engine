#include "DarkSprite.h"
#include "DarkDefs.h"
#include "DarkRect.h"
#include "Quad.h"
#include "WorldTransform.h"
#include "Texture.h"
#include "Dark.h"


CDarkSprite::CDarkSprite(DarkRect& rect_, char *texture)
{
	//Create Geometry (quad)
	m_quad = new Quad(0,0,rect_.GetWidth(), rect_.GetHeight());
	WorldTransform().SetPositionAbs(rect_.GetLeft(), rect_.GetTop(), rect_.GetDepth());
	
	
	//Store the TexturePath
	m_texturePath = texture;
	//Set Geometry no need for Render Property
	SetGeometry(m_quad);
}

CDarkSprite::~CDarkSprite(void)
{
	
}

//[Ishkaran] : Very Unoptimized I know
bool CDarkSprite::RenderSprite()
{
	//Get the texture from the Resource Manager
	CTexture& tex = (CTexture&)RESOURCE_MANAGER.GetResource(DRES_TEXTURE, m_texturePath );
	//Set the texture
	RENDER_DEVICE->SetTexture(0,tex.GetTexture());	//Set the texture
	return Render();	//Sets the Transform and then renders the Quad
}



void CDarkSprite::Tile(int x, int y)
{
	VERTEX* v = m_quad->GetQuadVertices();

	v[1].tu = x;
	v[2].tu = x; 
	v[2].tv = y;
	v[3].tv = y;

}

void CDarkSprite::ScrollX(float dir_, float speed_)
{
	VERTEX* v = m_quad->GetQuadVertices();

	v[0].tu += dir_*speed_;
	v[1].tu += dir_*speed_;
	v[2].tu += dir_*speed_;
	v[3].tu += dir_*speed_;
	v[2].tv = 1;
	v[3].tv = 1;
}

void CDarkSprite::ScrollY(float dir_, float speed_)
{
	VERTEX* v = m_quad->GetQuadVertices();

	v[0].tv += dir_*speed_;
	v[1].tv += dir_*speed_;
	v[2].tv += dir_*speed_;
	v[3].tv += dir_*speed_;

}

void CDarkSprite::ScaleTexture(float x_, float y_)
{
	VERTEX* v = m_quad->GetQuadVertices();

	v[1].tu /= x_;
	v[2].tu /= x_;
	v[2].tv /= y_;
	v[3].tv /= y_;


}

void CDarkSprite::FlipX()
{
	VERTEX* v = m_quad->GetQuadVertices();

	v[0].tu *= -1;
	v[1].tu *= -1;
	v[2].tu *= -1;
	v[3].tu *= -1;

}

void CDarkSprite::FlipY()
{
	VERTEX* v = m_quad->GetQuadVertices();

	v[0].tv *= -1;
	v[1].tv *= -1;
	v[2].tv *= -1;
	v[3].tv *= -1;

}

void CDarkSprite::SetTextureRect(DarkRect& rect_,  char* texture_)
{
	VERTEX* v = m_quad->GetQuadVertices();		//Automatically sets the flag for updating vertex Buffer in next frame
	
	CTexture& tempTex = (CTexture&)RESOURCE_MANAGER.GetResource(DRES_TEXTURE, texture_);

	v[0].tu = rect_.GetLeft()/tempTex.GetWidth();
	v[1].tu = rect_.GetRight()/tempTex.GetWidth();
	v[2].tu = rect_.GetRight()/tempTex.GetWidth();
	v[3].tu = rect_.GetLeft()/tempTex.GetWidth();

	v[0].tv = rect_.GetTop()/tempTex.GetHeight();
	v[1].tv = rect_.GetTop()/tempTex.GetHeight();
	v[2].tv = rect_.GetBottom()/tempTex.GetHeight();
	v[3].tv = rect_.GetBottom()/tempTex.GetHeight();


}

void CDarkSprite::SetTextureRect(float x_, float y_, float width_, float height_,  char* texture_)
{
	VERTEX* v = m_quad->GetQuadVertices();		//Automatically sets the flag for updating vertex Buffer in next frame
	
	CTexture& tempTex = (CTexture&)RESOURCE_MANAGER.GetResource(DRES_TEXTURE, texture_);

	v[0].tu = x_/tempTex.GetWidth();
	v[1].tu = x_+width_/tempTex.GetWidth();
	v[2].tu = x_+width_/tempTex.GetWidth();
	v[3].tu = x_/tempTex.GetWidth();

	v[0].tv = y_/tempTex.GetHeight();
	v[1].tv = y_/tempTex.GetHeight();
	v[2].tv = y_+height_/tempTex.GetHeight();
	v[3].tv = y_+height_/tempTex.GetHeight();
}