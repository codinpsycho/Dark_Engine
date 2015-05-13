#include "VertexShader.h"
#include "DarkDefs.h"
#include "Dark.h"
using namespace DarkEngine;


CVertexShader::CVertexShader(IHeader& vertexShaderHeader)
{

	if(CompileShader(vertexShaderHeader.m_path))
		if(FAILED(RENDER_DEVICE->CreateVertexShader((DWORD*)m_shaderBuffer->GetBufferPointer(), &m_shader)))
		{
			m_shaderBuffer->Release();
			MESSAGE(vertexShaderHeader.m_path);
		}
	
}

CVertexShader::~CVertexShader(void)
{
	SAFE_RELEASE(m_shader);
	SAFE_RELEASE(m_shaderBuffer);
	SAFE_RELEASE(m_errorBuffer);
	SAFE_RELEASE(m_constTable);
}

bool CVertexShader::CompileShader(char *name_)
{
	if(FILE_EXISTS(name_))
	{
		//If ur still here then Compile
		if(SUCCEEDED(D3DXCompileShaderFromFile(name_,NULL,NULL,"vs_main",D3DXGetVertexShaderProfile(RENDER_DEVICE),NULL,&m_shaderBuffer,&m_errorBuffer,&m_constTable)))
			return true;
		else
		{

#ifdef _DEBUG
			MESSAGE((char*)m_errorBuffer->GetBufferPointer());
#endif

			LOG.Write((char*)m_errorBuffer->GetBufferPointer());
			OutputDebugString((char*)m_errorBuffer->GetBufferPointer());
			m_errorBuffer->Release();
			return false;

		}

		
	}

	//If file doesnt exist notify some fool
	MESSAGE(name_);
	return false;

}
