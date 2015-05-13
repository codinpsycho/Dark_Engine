//.....................................................
//		Dark Engine :: Resource Factory
//		Coded by Ishkaran Singh
//		27/3/12
//		I Game hard, I Code Harder
//.....................................................

#pragma once
#include <map>
using namespace::std;

//------------------------------------------------------------------------------------
//Forward class declaration
class IDarkResource;
class ICreate;
struct IHeader;
//-----------------------------------XXX-----------------------------------------------


class ResourceFactory 
{
	//Function Pointer that our factory expects
	typedef IDarkResource& (*callbackFunc)(IHeader*) ;	
	//STL::map<name,ICreate> ..... map<key,value>  
	typedef std::map<string,ICreate*> CallbackMap ;
	//Constructors/destructor and op= are private so no one can create/destroy/assign 
	ResourceFactory(void);	
	ResourceFactory(const ResourceFactory& rhs);
	ResourceFactory& operator= (const ResourceFactory& rhs);

public:
	virtual ~ResourceFactory(void);
	//Only access point
	static ResourceFactory& Instance()
	{
		//Only instance that is created
		static ResourceFactory obj;
		return obj;
	}
	//factory specific functions
	bool RegisterResource(string type, ICreate* creater);
	bool UnRegisterResource(string );
	IDarkResource* CreateResource(string, IHeader&); 



private:
	CallbackMap  m_callbacks;
	
};

//-----------------------------------XXX-----------------------------------------------