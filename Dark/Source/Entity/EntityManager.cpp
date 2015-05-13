#include "EntityManager.h"
#include "RenderEntity.h"
#include "RenderProperty.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Dark.h"
#include "IGeometry.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <vector>
using namespace DarkEngine;

EntityManager::EntityManager(void)
{
}

EntityManager::~EntityManager(void)
{
}


bool EntityManager::Register(RenderEntity& entity)
{
	char *tempPropName= entity.GetRenderProprety().GetName();
	RenderMap::iterator end = m_renderMap.end();

	for ( RenderMap::iterator  pos = m_renderMap.begin(); pos != end; ++pos )
	{
		char *temp = pos->first;
		//Check if these two render properties are equal,comparing their names
		//If i already have this kind of render property, just add the entity to corresponding vector
		if(strcmp(tempPropName, temp) == 0)
		{	
			pos->second.push_back(&entity);
			return true;
		}
	}

	//else
	//F#%$,  I haven't seen this kind of property, so we keep the new render property for ourself >:)
	std::vector<RenderEntity*> tempList;
	tempList.push_back(&entity);

	return m_renderMap.insert(RenderMap::value_type(tempPropName, tempList)).second;


}

//<Scope for Improvement>
bool EntityManager::RenderEntities()
{

	RenderMap::iterator end = m_renderMap.end();
	for (RenderMap::iterator end = m_renderMap.end(),pos = m_renderMap.begin(); pos != end; ++pos )
	{
		std::vector<RenderEntity*>& tempRenderEntities(pos->second);
		//Now get the Render Property of first element, it will be same for all entities int his list
		CRenderProperty tempProp = tempRenderEntities[0]->GetRenderProprety();
		//Set this render property for the Render Device
		PrepareRendering(tempProp);

		for (unsigned int size = tempRenderEntities.size(), i = 0; i < size; ++i)
		{
			//Now the properties are set, render all the entities
			tempRenderEntities[i]->Render();
		}
	}

	return true;
}

//Property contains the textures and shaders to be applied
bool EntityManager::PrepareRendering(CRenderProperty& property_)
{
	//Now set these Render Properties for Graphic card to use
	LPDIRECT3DDEVICE9 tempDevice = DarkEngine::Dark::Instance().GetRenderDevice();
	std::vector<char*>& tempTextures(property_.GetTextures());
	

	for (unsigned int size = tempTextures.size(), i = 0; i < size; ++i)
	{
		//1. Request Textures from Resource Manager textures
		CTexture& tempTex = (CTexture&)DarkEngine::ResourceManager::Instance().GetResource(DRES_TEXTURE, tempTextures[i]);

		//Set the texture in increasing sampler number
		tempDevice ->SetTexture(i , tempTex.GetTexture());

	}

	//Now after this set the vertex and pixel shaders	
	char* tempVShader = property_.GetVertexShader();
	char* tempPixelShader = property_.GetPixelShaders();
	
	//Get the shaders from Resource manager
	CVertexShader& vShader = (CVertexShader&)RESOURCE_MANAGER.GetResource(DRES_VERTEXSHADER, tempVShader);
	CPixelShader& pShader = (CPixelShader&)RESOURCE_MANAGER.GetResource(DRES_PIXELSHADER, tempPixelShader);
	
	//Now apply the actual Shaders
	tempDevice->SetVertexShader(vShader.GetShader());
	tempDevice->SetPixelShader(pShader.GetShader());
	
	return true;
}

//<Scope for Improvement>
bool EntityManager::UpdateEntites(float dt)
{
	RenderMap::iterator end = m_renderMap.end();
	for (RenderMap::iterator end = m_renderMap.end(),pos = m_renderMap.begin(); pos != end; ++pos )
	{
		std::vector<RenderEntity*> tempRenderEntities(pos->second);
		
		//Just cal their Update for now
		for (unsigned int size = tempRenderEntities.size(), i = 0; i < size; ++i)
		{
			//Now the properties are set, render all the entities
			tempRenderEntities[i]->Update(dt);
		}
	}

	return true;
}

