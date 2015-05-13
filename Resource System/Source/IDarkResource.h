//.....................................................
//		Dark Enigne :: Base class for all resources
//		Coded by Ishkaran Singh
//		27/3/12
//		I Game hard, I Code Harder
//.....................................................



#pragma once
#include "ICount.h"
#include "ICreate.h"

//Empty header structure, other resources can implement their own headers, by deriving from this
//and whatever data they want, then in their creator class, they can use it as they want
struct IHeader	
{
	char *m_path;
	IHeader() : m_path("")	{}
	IHeader(char* path_) : m_path(path_)	{}
};	

//------------------------------------------------------------------------------------
class IDarkResource  : public ICount
{
protected:
	IDarkResource()	{}
public:
	IDarkResource& Clone()	{ AddRef(); return *this;	}
	virtual ~IDarkResource(void);
};
//-----------------------------------XXX-----------------------------------------------