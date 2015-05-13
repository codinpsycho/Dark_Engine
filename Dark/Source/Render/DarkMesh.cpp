#include "DarkMesh.h"
#include "WorldTransform.h"
#include "Dark.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "ResourceManager.h"


CDarkMesh::CDarkMesh(char *path_)
{
	if(FAILED(D3DXLoadMeshFromX(path_,
		D3DXMESH_MANAGED,
		RENDER_DEVICE,
		&m_adjacency,
		&m_attributes, 
		&m_effectInstances,
		&m_numAttributes,
		&m_mesh	)))
		LOG.Write("Mesh Load failed : %s",path_);
	else
	{

		D3DXMATERIAL* meshMaterials = (D3DXMATERIAL*)m_attributes->GetBufferPointer();
		
		//Now u got the textures needed for this mesh
		//Tell your Resource Manager to load them properly
		//[Ishkaran]: But then it will create unnecessary coupling with Resource Manager :(

		for (unsigned int i = 0; i < m_numAttributes; ++i)
		{
			if(meshMaterials[i].pTextureFilename && strlen(meshMaterials[i].pTextureFilename))
			{
				TextureHeader info;
				info.m_path = meshMaterials[i].pTextureFilename;
				m_vTextures.push_back(meshMaterials[i].pTextureFilename);	//Store it for later

				RESOURCE_MANAGER.CreateResource(DRES_TEXTURE, info);
			}
		}
		DWORD* adjacency = (DWORD*)m_adjacency->GetBufferPointer();
	}
	

	
}

CDarkMesh::~CDarkMesh(void)
{
	SAFE_RELEASE(m_mesh) ;
	SAFE_RELEASE(m_attributes);
	SAFE_RELEASE(m_adjacency);
	SAFE_RELEASE(m_effectInstances);
}

bool CDarkMesh::DrawGeometry(LPDIRECT3DDEVICE9 device)
{
	for (unsigned int i = 0; i < m_numAttributes; ++i)
	{
		if(FAILED(m_mesh->DrawSubset(i)))
			return false;
	}
	return true;
		
}
