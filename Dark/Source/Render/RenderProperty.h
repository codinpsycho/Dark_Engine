#pragma once
#include <vector>
using namespace::std;

class CRenderProperty
{
public:
	explicit CRenderProperty(char* name_ = "");
	virtual ~CRenderProperty(void);
	void AddTexture(char* path)					{ if(path) m_Textures.push_back(path);		}
	void AddNormalMap(char* path)				{ if(path) m_normalMaps.push_back(path);	}	 	
	void AddVertexShader(char* path)			{ if(path) m_vertexShader = path;			}
	void AddPixelShader(char* path)				{ if(path) m_pixelShader = path;			}
	std::vector<char *>& GetTextures()			{ return m_Textures;						}
	std::vector<char *>& GetNormalMaps()		{ return m_normalMaps;						}
	char* GetVertexShader()						{ return m_pixelShader;						}
	char* GetPixelShaders()						{ return m_vertexShader;					}
	char* GetName()	const						{ return m_name;							}

private:
	//Textures and shaders are contained as path and not as actual data, actual data is contained in ResourceManager
	std::vector<char *> m_Textures;
	std::vector<char *> m_normalMaps;
	char * m_vertexShader;
	char * m_pixelShader;
	char *m_name;
};
