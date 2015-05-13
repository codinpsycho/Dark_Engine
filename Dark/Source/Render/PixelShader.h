#ifndef _PIXEL_SHADER_H_
#define _PIXEL_SHADER_H_

#include "IDarkResource.h"
#include "Direct3D.h"
#include "ICreate.h"

class CPixelShader :	public IDarkResource
{
public:
	CPixelShader& Clone()	{ AddRef(); return *this;	}
	LPDIRECT3DPIXELSHADER9 GetShader()	{ return m_pixelShader;	}
	
	virtual ~CPixelShader(void);
private:
	//To access private constructor of CPixelShader
	friend class CPixelShaderCreator;

	bool CompileShader(char *);
	CPixelShader(IHeader& pixelShaderHeader);
	LPDIRECT3DPIXELSHADER9 m_pixelShader;
	LPD3DXBUFFER m_shaderBuffer;
	LPD3DXBUFFER m_errorBuffer;
	LPD3DXCONSTANTTABLE m_constTable;
	char *m_name;
};


class CPixelShaderCreator : public ICreate
{
public:
	IDarkResource* Create(IHeader& pixelShaderHeader)
	{
		return new CPixelShader(pixelShaderHeader);
	}
	CPixelShaderCreator (void)	{}
	~CPixelShaderCreator (void)	{}
};


#endif
