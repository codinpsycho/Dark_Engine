//.....................................................
//		Dark Engine :: Interface for resource creation
//		Coded by Ishkaran Singh
//		27/3/12
//		I Game hard, I Code Harder
//.....................................................


#pragma once

class IDarkResource;
struct IHeader;

//------------------------------------------------------------------------------------
class ICreate
{

public:
	
	virtual IDarkResource* Create(IHeader&) = 0;
	virtual ~ICreate(void)	{}
	ICreate(void)	{}

};
//-----------------------------------XXX-----------------------------------------------