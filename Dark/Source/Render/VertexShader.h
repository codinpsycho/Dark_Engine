#ifndef _VERTEX_SHADER_H_
#define _VERTEX_SHADER_H_

#include "IDarkResource.h"
#include "Direct3D.h"
#include "ICreate.h"

class CVertexShader :	public IDarkResource
{
public:
	CVertexShader& Clone()	{ AddRef(); return *this;	}

	LPDIRECT3DVERTEXSHADER9 GetShader()	{ return m_shader;	}

	virtual ~CVertexShader(void);
private:

	//Friend class to access CVertexShader constructor
	friend class CVertexShaderCreator;
	CVertexShader(IHeader& vertexShaderHeader);
	bool CompileShader(char *name_);
	LPDIRECT3DVERTEXSHADER9 m_shader;
	LPD3DXBUFFER m_shaderBuffer;
	LPD3DXBUFFER m_errorBuffer;
	LPD3DXCONSTANTTABLE m_constTable;
	char *m_name;
	
};


class CVertexShaderCreator : public ICreate
{
public:
	IDarkResource* Create(IHeader& vertexShaderHeader)
	{
		return new CVertexShader(vertexShaderHeader);
	}
	CVertexShaderCreator (void)	{}
	~CVertexShaderCreator (void)	{}
};


#endif
