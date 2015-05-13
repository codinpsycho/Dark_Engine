#pragma
#include <string>
#include <map>


//Forward classes
class IScene;

namespace DarkEngine
{
	class SceneManager
	{
		
	public:
		static SceneManager& Instance()
		{
			static SceneManager obj;
			return obj;
		}
		bool SetTempCurrentState();
		bool SetCurrentScene(std::string name);					//Makes the passed scene name as current scene if registered
		bool RegisterScene(std::string name, IScene* scene);		//Maintains a std::map<string, iscene*>	of all scenes
		virtual ~SceneManager(void);

		
		bool Update(float dt);		//Calls current scenes Update
		bool Render();				//Calls current scenes Render
		

	private:

		bool Init();		//Calls current scenes init
		bool Release();		//Calls current scenes release
		typedef std::map<std::string,IScene*> SceneMap;
		SceneMap m_sceneMap;

		IScene *m_currentScene, *m_tempScene;
		//No one can create you 
		SceneManager(void) : m_currentScene(0), m_tempScene(0)	{}
		SceneManager(const SceneManager& rhs);
		SceneManager operator= ( SceneManager& rhs );
	};

}
