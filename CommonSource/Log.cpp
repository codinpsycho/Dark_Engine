#include "DarkDefs.h"		//Log.h included in this
#include <stdarg.h>


Log::Log(void) : m_file(0)
{
  AttachFile("log.txt");
}


Log::~Log(void)
{
	Write("All right, Everything destroyed, Self Destructing now \nBye Bye :) :)\n\nI Game Hard, I Code Harder");
	if(m_file)
		fclose(m_file);
	
}


bool Log::AttachFile(char *fileName)
{
	
	m_file = fopen(fileName, "w+");
	//Check if successful
	if(m_file)
		return true;
	else
		return false;
		
}

int Log::Write(const char* format,...)
{
	assert(m_file); 

	va_list list;
	char buff[1024];							//Buffer to hold final output
	size_t size = sizeof(buff);
	ClearDarkMemory(buff,sizeof(buff));				//0 out the memory
	//buff[size]	= '\0';							//To keep it null terminated
	//buff[size - 1]	= '\n';						//To keep it in Human readable form
	va_start(list, format);					//Start iterating
	vsnprintf(buff, size - 2, format, list );	//Print into Buffer
	va_end(list);								//Free the memory used by list

	return fputs(buff, m_file);	
	
}

