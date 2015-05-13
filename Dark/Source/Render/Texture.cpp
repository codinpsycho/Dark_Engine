#include "Texture.h"
#include "Dark.h"
using namespace DarkEngine;

// 
// CTexture::CTexture(void): IResource(this, TEXTURE)
// {
// 	m_texture = 0;
// 	m_material = 0;
// }

CTexture::~CTexture(void)
{
	SAFE_RELEASE(m_texture);

	/*if(m_material)	m_material->Release();*/
}
// 
// CTexture::CTexture(const WCHAR* path_) : IResource(this, TEXTURE)
// {
// 	m_material = new CMaterial;
// 	m_material->Initialize();
// 	TextureHeader params_;
// 	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(EngineManager::Instance()->GetD3DDevice(),path_,params_.width,params_.height,params_.mipLevel,params_.usage,params_.format,params_.memoryPool,params_.filtering,params_.mipFilter,params_.colorKey,&m_info,NULL,&m_texture)))
// 		message(path_,ERROR);
// 	
// 	
// }
// 
// CTexture::CTexture( WCHAR* path_, CMaterial* material_) : IResource(this, TEXTURE)
// {
// 	m_material = material_->Reference();
// 	TEXTURE_DESC params_;
// 	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(EngineManager::Instance()->GetD3DDevice(),path_,m_textureParams.width,m_textureParams.height,m_textureParams.mipLevel,m_textureParams.usage,m_textureParams.format,m_textureParams.memoryPool,m_textureParams.filtering,m_textureParams.mipFilter,m_textureParams.colorKey,&m_info,NULL,&m_texture)))
// 		message(path_,ERROR);
// 	
// }
// 
// 
// CTexture::CTexture( WCHAR* path_, float width_, float height_,DWORD usage_, DWORD mipLevel_): IResource(this, TEXTURE)
// {
// 	m_material = new CMaterial;
// 	m_material->Initialize();
// 	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(EngineManager::Instance()->GetD3DDevice(),path_,width_,height_,mipLevel_,usage_,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_FILTER_NONE,NULL,0,&m_info,NULL,&m_texture)))
// 		message(path_,ERROR);
// }
// 
CTexture::CTexture( TextureHeader& params_)
{
// 	m_material = new CMaterial;
// 	m_material->Initialize();
	
	if(FILE_EXISTS(params_.m_path))
	{
		if (FAILED(D3DXCreateTextureFromFileEx(DarkEngine::Dark::Instance().GetRenderDevice(), params_.m_path,params_.width,params_.height,params_.mipLevel,params_.usage,params_.format,params_.memoryPool,params_.filtering,params_.mipFilter,params_.colorKey,&m_info,NULL,&m_texture)))
		{
			char buff[256];
			sprintf(buff,"%s%s",  params_.m_path);	
			MESSAGE(buff);
		}
	}
	else
	{
		char buff[256];
		sprintf(buff,"%s%s", "File Not Found\n", params_.m_path);	
		MESSAGE(buff);
	}


}

// 
// PIXEL CTexture::GetPixel(int x_, int y_)
// {
// 	if(!m_texture)
// 	{
// 		message(L"Cannot convert to black and white",L"ERROR");
// 		PIXEL p;
// 		return p;
// 	}
// 	else if(x_ > m_info.Width || y_ > m_info.Height)
// 	{
// 		message(L"Invalid pixel location",L"ERROR");
// 		PIXEL p;
// 		return p;
// 	}
// 	
// 	D3DLOCKED_RECT rect;
// 	DWORD *pixelData;
// 	m_texture->LockRect(0,&rect,NULL,0);
// 	pixelData = (DWORD*)rect.pBits;
// 	m_texture->UnlockRect(0);
// 	y_ = rect.Pitch*y_;
// 	x_ += y_;
// 	pixelData += x_;
// 	
// 	 PIXEL p;
// 	 p.a = (*pixelData & 0xff000000) >> 24;
// 	 p.r = (*pixelData & 0x00ff0000) >> 16;
// 	 p.g = (*pixelData & 0x0000ff00) >> 8;
// 	 p.b = (*pixelData & 0x000000ff) ;
// 	 return p;
// 
// }

// 
// bool CTexture::SetPixel(int x_, int y_, DWORD color_)
// {
// 	if(m_texture == NULL)
// 	{
// 		message(L"Cannot convert to black and white",L"ERROR");
// 		return false;
// 	}
// // 	else if(x_ > m_texture->Width || y_ > m_texture->Height)
// // 	{
// // 		message(L"Invalid pixel location",L"ERROR");
// // 		return false;
// // 	}
// 	D3DLOCKED_RECT rect;
// 	DWORD *pixelData;
// 	m_texture->LockRect(0,&rect,NULL,0);
// 	pixelData = (DWORD*)rect.pBits;
// 	m_texture->UnlockRect(0);
// 	y_ = (rect.Pitch*y_);
// 	x_ += y_;
// 	pixelData += x_;
// 	//Extracting colors from pixeldata
// // 	unsigned WCHAR alpha = (*pixelData & 0xff000000) >> 24;
// // 	unsigned WCHAR red = (*pixelData & 0x00ff0000) >> 16;
// // 	unsigned WCHAR green = (*pixelData & 0x0000ff00) >> 8;
// // 	unsigned WCHAR blue = (*pixelData & 0x000000ff) ;
// 	if(pixelData)
// 	{
// 	unsigned char alpha1 = (color_ & 0xff000000) >> 24;
// 	unsigned char red1 = (color_ & 0x00ff0000) >> 16;
// 	unsigned char green1 = (color_ & 0x0000ff00) >> 8;
// 	unsigned char blue1 = (color_ & 0x000000ff) ;
// 	
// 	*pixelData = (alpha1 << 24) | (red1 <<16) | (green1 << 8) | (blue1);
// 	}
// 	return true;
// }
//Constructors for Texture Header
TextureHeader::TextureHeader()
{
	usage = NULL;
	mipLevel= D3DX_DEFAULT; 
	memoryPool= D3DPOOL_MANAGED;
	colorKey= D3DX_DEFAULT;
	format= D3DFMT_UNKNOWN;
	filtering= D3DX_DEFAULT;
	mipFilter= D3DX_DEFAULT;
	width = 0;
	height = 0;
}

TextureHeader::TextureHeader(char* path_) : IHeader(path_)
{
	usage = NULL;
	mipLevel= D3DX_DEFAULT; 
	memoryPool= D3DPOOL_MANAGED;
	colorKey= D3DX_DEFAULT;
	format= D3DFMT_UNKNOWN;
	filtering= D3DX_DEFAULT;
	mipFilter= D3DX_DEFAULT;
	width = 0;
	height = 0;
}
// 
// void CTexture::Modulate(COLORVALUE color_)
// {
// 	m_material->SetDiffuse(color_);
// }
// 
// void CTexture::Modulate(CTexture* texture_)
// {
// 	if(!texture_)
// 	{
// 		message(L"Pass a valid texture",L"ERROR");
// 		return;
// 	}
// 	EngineManager::Instance()->ClearTextureStage();
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(0,this->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLORARG0,D3DTA_TEXTURE);
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(1,texture_->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLOROP,D3DTOP_MODULATE);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG2,D3DTA_TEXTURE);
// 	
// }
// 
// void CTexture::Modulate2x(CTexture* texture_)
// {
// 	if(!texture_)
// 	{
// 		message(L"Pass a valid texture",L"ERROR");
// 		return;
// 	}
// 	EngineManager::Instance()->ClearTextureStage();
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(0,this->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(1,texture_->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLOROP,D3DTOP_MODULATE2X);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG2,D3DTA_TEXTURE);
// 	
// }
// 
// void CTexture::Modulate4x(CTexture* texture_)
// {
// 	if(!texture_)
// 	{
// 		message(L"Pass a valid texture",L"ERROR");
// 		return;
// 	}
// 	EngineManager::Instance()->ClearTextureStage();
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(0,this->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(1,texture_->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLOROP,D3DTOP_MODULATE4X);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG2,D3DTA_TEXTURE);
// 	
// }
// 
// void CTexture::Add(CTexture* texture_)
// {
// 	if(!texture_)
// 	{
// 		message(L"Pass a valid texture",L"ERROR");
// 		return;
// 	}
// 	EngineManager::Instance()->ClearTextureStage();
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(0,this->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(1,texture_->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLOROP,D3DTOP_ADD);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG2,D3DTA_TEXTURE);
// 	
// }
// 
// void CTexture::AddSigned(CTexture* texture_)
// {
// 	if(!texture_)
// 	{
// 		message(L"Pass a valid texture",L"ERROR");
// 		return;
// 	}
// 	
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(0,texture_->GetTexture());
// 	
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
// 	EngineManager::Instance()->GetD3DDevice()->SetTexture(1,this->GetTexture());
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLOROP,D3DTOP_ADDSIGNED);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
// 	EngineManager::Instance()->GetD3DDevice()->SetTextureStageState(1,D3DTSS_COLORARG2,D3DTA_TEXTURE);
// 	
// 	
// }
// 

//  bool CTexture::LoadTexture(const WCHAR* path_, TEXTURE_DESC& params_)
// {
// 	if(m_texture)	m_texture->Release();
// 	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(EngineManager::Instance()->GetD3DDevice(),path_,params_.width,params_.height,params_.mipLevel,params_.usage,params_.format,params_.memoryPool,params_.filtering,params_.mipFilter,params_.colorKey,&m_info,NULL,&m_texture)))
// 	{
// 		message(path_,ERROR);
// 		return false;
// 	}
// 	return true;
// }