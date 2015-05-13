#include "SceneManager.h"
#include "Log.h"
#include "IScene.h"
#include "DarkDefs.h"
using namespace DarkEngine;


SceneManager::~SceneManager(void)
{
	
	//destroy sceneMap and keep ur heap clear
	Log::Instance()<<"Destroying Scene Manager\n";

	SceneManager::SceneMap::iterator end = m_sceneMap.end();
	//Destroy the scenes that were created
	for ( SceneManager::SceneMap::iterator curr = m_sceneMap.begin(); curr != end; ++curr)
	{
		SAFE_DELETE(curr->second);
	}

	//No need to delete them the memory they were pointing to has been deleted i the loop :)
// 	SAFE_DELETE(m_currentScene);
// 	SAFE_DELETE(m_tempScene);

}


bool SceneManager::RegisterScene(std::string name, IScene* scene)
{
	//Registers new scene into Log file
	std::string buff("Registering new scene : ");
	buff += name; 
	buff += "\n";
	Log::Instance()<<buff.c_str();

	//Return true, if successfully added to the list
	return m_sceneMap.insert(SceneMap::value_type(name, scene)).second;
		
}

bool SceneManager::SetCurrentScene(std::string name)
{
	//Add levels name into Log file
	std::string buff("Changing current scene to : ");
	buff += name; 
	buff += "\n";
	Log::Instance()<<buff.c_str();
	
	//Now check if the required scene is registered with u or not
	SceneMap::iterator tempScene = m_sceneMap.find(name);
	
	if( tempScene != m_sceneMap.end())
	{
		//It means we have found the scene
		//Now if current scene is valid, then tell it to release its resources
		if(m_currentScene)
			m_currentScene->Release();
		m_currentScene = tempScene->second;

		//Now call init() of the newly created scene
		m_currentScene->Initialize();

	}
	
	return true;
}


bool SceneManager::Render()
{

#ifdef _DEBUG
	assert(m_currentScene);
#endif

	return m_currentScene->Render();
}


bool SceneManager::Update(float dt)
{

#ifdef _DEBUG
	assert(m_currentScene);
#endif

	return m_currentScene->Update(dt);
}
