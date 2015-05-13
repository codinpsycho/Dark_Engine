//.....................................................
//		Dark Engine :: Resource Manager 
//		Coded by Ishkaran Singh
//		27/3/12
//		I Game hard, I Code Harder
//.....................................................


#pragma once
#include <map>
#include <vector>

//------------------------------------------------------------------------------------
//Forward declarations
class ICreate;
class IDarkResource;
struct Resource;
struct IHeader;
//-----------------------------------XXX-----------------------------------------------


namespace DarkEngine
{
	//------------------------------------------------------------------------------------
	class ResourceManager
	{

		//same data within factory and manager :( :(

		//Function Pointer that our factory expects
		typedef IDarkResource& (*callbackFunc)(IHeader&) ;	
		//STL::map<name,function> ..... map<key,value>  
		typedef std::map<std::string,callbackFunc> CallbackMap ;
		typedef std::map<std::string, std::vector<Resource>> ResourceMap;

		//No one can create u >:)
		ResourceManager(void);
		ResourceManager(const ResourceManager& rhs);
		ResourceManager& operator= (const ResourceManager& rhs);

	public:
		
		static ResourceManager& Instance()
		{
			//Only instance that is created
			static ResourceManager obj;
			return obj;
		}
		//But everyone can destroy u >:D
		bool ShutDown();
		virtual ~ResourceManager(void);

		//Basic functions
		bool RegisterResource(char*,  ICreate* creater);
		bool UnRegisterResource(char*);
		IDarkResource& CreateResource(char*, IHeader&); 
		IDarkResource& GetResource(char* type, char* path);

	private:
		ResourceMap m_resourceMap;
	};

	//-----------------------------------XXX-----------------------------------------------
}



