//.....................................................
//		Dark Engine :: Mesh Class 
//		Coded by Ishkaran Singh
//		29/Apr/12
//		I Game hard, I Code Harder
//.....................................................


#ifndef DARK_MESH_H_
#define DARK_MESH_H_

#include "IGeometry.h"
#include "IDarkResource.h"
#include "DarkDefs.h"


enum eMESHTYPE { X, OBJ };		//Different formats that we can load

//Forward Declarations
class CMeshLoader;

//Header
struct MeshHeader : public IHeader
{
	eMESHTYPE type;	
	MeshHeader(char *path_) : IHeader(path_)
	{ type = X;	}
};

class CDarkMesh :  public IDarkResource, public IGeometry
{
	
public:
	
	virtual ~CDarkMesh(void);
	bool DrawGeometry(LPDIRECT3DDEVICE9 device);
	int GetVertexCount()							{ return m_mesh->GetNumVertices();	}
	int GetGeometryCount()							{ return m_numAttributes;			}	//Attributes in case of mesh(SubMeshes)
	bool Update(float dt, LPDIRECT3DDEVICE9 device)	{ return true; /*Physics Update*/	}
	friend class CMeshLoader;

private:

	

	CDarkMesh(char *path_);
	LPD3DXMESH m_mesh;
	LPD3DXBUFFER m_attributes;
	LPD3DXBUFFER m_adjacency;
	LPD3DXBUFFER m_effectInstances;
	DWORD m_numAttributes;
	std::vector<char*> m_vTextures;

};

//You need a Mesh Creator to create this ugly dark Mesh
class CMeshLoader : public ICreate
{
	IDarkResource* Create(IHeader& header_)
	{
		MeshHeader& mHeader = (MeshHeader&)header_;
		switch (mHeader .type)
		{
		case X:
			return LoadXMesh(mHeader .m_path);
		}
	}
	IDarkResource* LoadXMesh(char *path)	{ return new CDarkMesh(path);	}
};


#endif

