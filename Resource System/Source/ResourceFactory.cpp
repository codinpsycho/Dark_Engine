#include "ResourceFactory.h"
#include <string>
#include "ResourceManager.h"
#include "ICreate.h"
#include "DarkDefs.h"
#include "Log.h"
ResourceFactory::ResourceFactory(void)
{

}


//------------------------------------------------------------------------------------
ResourceFactory::~ResourceFactory(void)
{
	Log::Instance()<<"Destroying Resource Factory\n";
	//Clear the map
	m_callbacks.clear();
}
//-----------------------------------XXX-----------------------------------------------


//------------------------------------------------------------------------------------
bool ResourceFactory::RegisterResource(string type, ICreate* creater)
{
	string temp("Registering new Resource type : ");
	temp += type;
	temp += "\n";
	Log::Instance()<<temp.c_str();
	//map::value_type is a typedef for actual std::map<key, value>;
	//insert returns a pair with a value and a bool, if value existed before --> false else true
	return 	m_callbacks.insert(CallbackMap::value_type(type, creater)).second;
}
//-----------------------------------XXX-----------------------------------------------


//------------------------------------------------------------------------------------
bool ResourceFactory::UnRegisterResource( string type )
{
	string temp("Removing Resource type : ");
	temp += type;
	temp += "\n";
	Log::Instance()<<temp.c_str();
	//erase returns number of elements removed
	//for map it can be only 0 or 1, multimap it can be 0,1,more
	return (m_callbacks.erase(type) == 1);
}
//-----------------------------------XXX-----------------------------------------------


//------------------------------------------------------------------------------------
IDarkResource* ResourceFactory::CreateResource(string type, IHeader& header)
{
	//find(key) returns iterator to element or end if not found
	CallbackMap::iterator pos = m_callbacks.find(type);
	if( pos != m_callbacks.end())
	{
		//Call the actual function and pass  the header
		return (pos->second->Create(header));


	}
	else
	{ 
		string temp(type);
		temp += " : Not supported";
		MESSAGE(temp.c_str()) ;
	}

}
//-----------------------------------XXX-----------------------------------------------
