#pragma once
#include <fstream>
#include <assert.h>


class Log
{
	
public:
	static Log& Instance()
	{
		static Log obj;
		return obj;
	}
	
	bool  AttachFile(char *fileName);
	int operator<<(const char *data )	{ assert(m_file); return fputs(data, m_file);	}
	int Write(const char* data,...);	
	virtual ~Log(void);

private:
	Log(void);
	Log(const Log& rhs);
	Log operator=(Log& rhs) ;
	
	//Data Members
	FILE* m_file;
};
