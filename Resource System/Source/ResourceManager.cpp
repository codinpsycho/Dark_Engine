#include "ResourceManager.h"
#include "ResourceFactory.h"
#include <string>
#include "IDarkResource.h"
#include "Log.h"
#include "DarkDefs.h"
using namespace DarkEngine;


//------------------------------------------------------------------------------------
//All resources are stored as this struct
struct Resource
{
	IDarkResource* resource;
	//This is for identifying the resource
	char *path;
};
//-----------------------------------XXX-----------------------------------------------

ResourceManager::ResourceManager(void)
{
}

ResourceManager::~ResourceManager(void)
{
	Log::Instance()<<"Destroying Resource Manager\n";
	//Todo : check for memory leak
}

//------------------------------------------------------------------------------------
//Registers resource with itself and the factory as well
bool ResourceManager::RegisterResource(char* type, ICreate* creater)
{
	
	std::vector<Resource> array;
	//First associate with the manager, If manager approves, send the equipments to factory 
	if(m_resourceMap.insert(ResourceMap::value_type(type, array)).second)
		//All is well, All is well
		return ResourceFactory::Instance().RegisterResource(type, creater);
	else
	{
		string temp(type);
		temp += " : Registeration failed";
		MESSAGE(temp.c_str());
		return false;
	}
}
//-----------------------------------XXX-----------------------------------------------

//------------------------------------------------------------------------------------
//Removes the resource type from factory
//But it retains with itself created resources of this type, if any
bool ResourceManager::UnRegisterResource(char* type)
{
	return ResourceFactory::Instance().UnRegisterResource( type );
}
//-----------------------------------XXX-----------------------------------------------


//------------------------------------------------------------------------------------
//Path of the file is contained in the header
IDarkResource& ResourceManager::CreateResource(char* type, IHeader& header)
{
	ResourceMap::iterator end = m_resourceMap.end();
	//First check wether u already have it or not
	ResourceMap::iterator pos = m_resourceMap.find(type);

	if(pos != end)
	{
		//Get the appropriate vector of resources
		std::vector<Resource>& tempList = pos->second;
		//Check if u r a loser or not
		int size = tempList.size();
		for (int i = 0; i < size; ++i )
		{
			if(_strcmpi(tempList[i].path, header.m_path) == 0)	{}
				//if u are here, den u r really a loser, y d F#@% u creating same resources >:(
				return tempList[i].resource->Clone();
		}

		//Well u passed the test :)
		Resource tempRes;
		tempRes.resource = ResourceFactory::Instance().CreateResource(type,header);
		tempRes.path = header.m_path;
		//Store the resource struct
		tempList.push_back(tempRes);
		//Now be a good boy n return it 
		return *(tempRes.resource);

	}
	else
	{
		/*U really suck man, I dont create these kind of resources */ 
		string temp(type);
		temp += " : Not supported \n Cannot create this kind of resource";
		MESSAGE(temp.c_str());
		//Here we dont know what kind of resource to return, so cant return a null resource
	}
		
}
//-----------------------------------XXX-----------------------------------------------



//------------------------------------------------------------------------------------
//Gets u reference of the resource if it conatins one
//else gives u a null resource
IDarkResource& ResourceManager::GetResource(char* type, char* path)
{
	ResourceMap::iterator pos = m_resourceMap.find(type);
	//Check if we support this kind of resource
	if(pos != m_resourceMap.end())
	{
		//Make sure the path is correct
		if(FILE_EXISTS(path))
		{
			//Get the appropriate vector of resources
			//Take a reference so no temporary is created
			std::vector<Resource>& tempList = pos->second;
			//Check if u r a loser or not
			
			//0 is reserved for Default resources
			for (int size = tempList.size(), i = 0; i < size; ++i )
			{
				//Found :)
				if(_strcmpi(tempList[i].path, path) == 0)
					return *(tempList[i].resource);
				else
				{	
					/*Pathetic man, who the F#@%'s goin to create the resource first >:(*/ 
					//No need to mess your output window
				}
				
			}
		}
		else
		{
			//if we are here, then we dint find the file
			//No need to mess your output window
			
			//return a default texture (At 0, null resources are present for corresponding kind)
			return *(pos->second[0].resource);
		}
	}
	else
	{ 
		/*U really suck man, we dont have these kind of resources >:(*/ 
		//No need to mess your output window
	}



}
//-----------------------------------XXX-----------------------------------------------


//------------------------------------------------------------------------------------
//Checks if some one forgot to release the resources
bool ResourceManager::ShutDown()
{
	//TODO
	return true;
	
}
//-----------------------------------XXX-----------------------------------------------