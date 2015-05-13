#pragma once
#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "Direct3D.h"
#include "IDarkResource.h"
#include "ICreate.h"
class Rect;


struct PIXEL 
{
	unsigned char a;	
	unsigned char r;
	unsigned char g;
	unsigned char b;
	PIXEL()
	{
		a = r = g = b = 0;
	}
};


struct TextureHeader : public IHeader
{
	DWORD usage;
	DWORD mipLevel;
	D3DPOOL memoryPool;
	DWORD colorKey;
	D3DFORMAT format;
	DWORD filtering;
	DWORD mipFilter;
	DWORD width;
	DWORD height;
	TextureHeader();
	TextureHeader(char* path_);	
};

class CTextureCreator;

class CTexture : public IDarkResource
{
public:
	

	LPDIRECT3DTEXTURE9 GetTexture() const	{ return m_texture; }			//Loads texture into memory
	D3DXIMAGE_INFO* GetD3DImageInfo()	{ return &m_info; }
	PIXEL GetPixel(int x_, int y_);
	bool SetPixel(int x_, int y_, DWORD);
	
	UINT GetWidth()		{ return m_info.Width; }
	UINT GetHeight()		{ return m_info.Height; }
	
	virtual ~CTexture(void);
	void Modulate(COLORVALUE);		//Multiplies this color with the image
	void Modulate2x(COLORVALUE);		//Multiplies the color then doubles the result Use for brightening
	void Modulate4x(COLORVALUE);		//Multiplies the color then quadruples the result Use for brightening
	void Add(COLORVALUE);			//Adds the color to the Image
	void Subtract(COLORVALUE);		//Subtracts the color from the image
	void AddSigned(COLORVALUE);		//Adds the color then subtracts 0.5 to avoid over brightening

	void Modulate(CTexture*);		//Multiplies this texture with the image
	void Modulate2x(CTexture*);		//Multiplies the texture then doubles the result Use for brightening
	void Modulate4x(CTexture*);		//Multiplies the texture then quadruples the result Use for brightening
	void Add(CTexture*);			//Adds the texture to the Image
	void Subtract(CTexture*);		//Subtracts the texture from the image
	void AddSigned(CTexture*);		//Adds the texture then subtracts 0.5 to avoid over brightening
	CTexture& operator+(CTexture& rhs);
private:
	friend class CTextureCreator;
	//Only the resource factory can create you 
	CTexture(void);
 	CTexture( TextureHeader& params_);		
	CTexture(const CTexture& rhs)	{}
	LPDIRECT3DTEXTURE9 m_texture;
	D3DXIMAGE_INFO m_info;
	TextureHeader m_textureParams;

};



class CTextureCreator : public ICreate
{
public:
	IDarkResource* Create(IHeader& textureHeader)
	{
		TextureHeader& tempHeader = (TextureHeader&)textureHeader;
		return new CTexture(tempHeader);
	}
	CTextureCreator(void)	{}
	~CTextureCreator(void)	{}
};




#endif
