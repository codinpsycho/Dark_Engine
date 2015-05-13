#include "GraphicsManager.h"
#include "Text.h"
#include "Dark.h"
#include "DarkSprite.h"
using namespace DarkEngine;

CGraphicsManager::CGraphicsManager(void)
{
	m_text = new Text;
	if(!m_text->Create2DText(RENDER_DEVICE, "Arial", 16))
	{
		LOG.Write("Create 2D text failed");
		SAFE_DELETE(m_text);	//No need for u now
	}


}

void CGraphicsManager::SetTextParams(char *font_, int size)
{
	if(font_)
	{
		if(!m_text->Create2DText(RENDER_DEVICE, "font", size))
		{
			LOG.Write("Create 2D text failed");
			SAFE_DELETE(m_text);	//No need for u now
		}
		
	}
		
	
}

CGraphicsManager::~CGraphicsManager(void)
{
}


bool CGraphicsManager::ShowText(int xPos, int yPos, int width, int height, COLOR color, char *text,...) 
{
	assert(m_text);

	va_list list;
	char buff[2048];							//Buffer to hold final output
	size_t size = sizeof(buff);
	ZeroMemory(buff,sizeof(buff));				//0 out the memory

	va_start(list, text);						//Start iterating
	vsnprintf(buff, size - 3, text, list );		//Print into Buffer
	va_end(list);								//Free the memory used by list

	buff[size - 1]	= '\0';						//To keep it null terminated
	buff[size - 2]	= '\n';						//To keep it in Human readable form

	return m_text->Render2D(buff,xPos, yPos, width, height, color) ? true : false;
}


bool CGraphicsManager::ShowTexture(DarkRect& rect_, char *texture)
{
	
	CDarkSprite tempSprite(rect_, texture);
	return tempSprite.RenderSprite();

}
