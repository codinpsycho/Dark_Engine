#include "PixelShader.h"
#include "DarkDefs.h"
#include "Dark.h"
using namespace DarkEngine;



CPixelShader::CPixelShader(IHeader& pixelShaderHeader)
{
	//First compile the shader
		if(CompileShader(pixelShaderHeader.m_path))
			if(FAILED(RENDER_DEVICE->CreatePixelShader((DWORD*)m_shaderBuffer->GetBufferPointer(), &m_pixelShader)))
			{
				m_shaderBuffer->Release();
				MESSAGE(pixelShaderHeader.m_path);
			}
}

CPixelShader::~CPixelShader(void)
{
	SAFE_DELETE(m_name);
	SAFE_RELEASE(m_pixelShader);
	SAFE_RELEASE(m_shaderBuffer);
	SAFE_RELEASE(m_errorBuffer);
	SAFE_RELEASE(m_constTable);
}

bool CPixelShader::CompileShader(char *name_)
{

	if(FILE_EXISTS(name_))
	{
		//If ur still here then Compile
		D3DXCompileShaderFromFile(name_,NULL,NULL,"ps_main",D3DXGetPixelShaderProfile(RENDER_DEVICE),NULL,&m_shaderBuffer,&m_errorBuffer,&m_constTable);
		if(!m_errorBuffer)
			return true;
		else
		{
		//Must be some error in the shader
#ifdef _DEBUG
			MESSAGE((char*)m_errorBuffer->GetBufferPointer());
#endif
			
			LOG.Write((char*)m_errorBuffer->GetBufferPointer());
			OutputDebugString((char*)m_errorBuffer->GetBufferPointer());
			m_errorBuffer->Release();
			return false;

		}
		return true;
	}
	//If file doesnt exist notify some fool
	MESSAGE(name_);
	return false;
	
}
