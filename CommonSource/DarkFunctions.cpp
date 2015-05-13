#include <vector>
#include "DarkDefs.h"
using namespace::std;

//Code to delete vector pointing to memory locations
template<class T>
void DeleteVector(std::vector<T> &list)
{
	int size = list.size() - 1;
	while(!list.empty())
	{
		delete list[size];
		list.pop_back();
		--size;
	}
}

//Code to Release vector pointing to memory locations
template<class T>
void ReleaseVector(std::vector<T> &list)
{
	int size = list.size() - 1;
	while(!list.empty())
	{
		list[size].Release();
		list.pop_back();
		--size;
	}
}

//General printf like function used to print into output window
void OutputString(char *format_, ...)
{
	va_list list;
	char buff[2048];							//Buffer to hold final output
	size_t size = sizeof(buff);
	ZeroMemory(buff,sizeof(buff));				//0 out the memory

	va_start(list, format_);					//Start iterating
	vsnprintf(buff, size - 3, format_, list );	//Print into Buffer
	va_end(list);								//Free the memory used by list

	buff[size - 1]	= '\0';							//To keep it null terminated
	buff[size - 2]	= '\n';						//To keep it in Human readable form
	
	OutputDebugString(buff);					//Only works in Debug mode :(

}

