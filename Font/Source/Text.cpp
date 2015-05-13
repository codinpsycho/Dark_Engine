#include "Text.h"
#include <assert.h>
#include "DarkDefs.h"
#include "WorldTransform.h"

Text::Text(void) : m_text(0), m_worldTransform(0), m_textMesh(0)
{
}

Text::~Text(void)
{
	SAFE_RELEASE(m_text);
	SAFE_RELEASE(m_textMesh);
	SAFE_DELETE(m_worldTransform);
}

bool Text::Create2DText(LPDIRECT3DDEVICE9 device, char* faceName, int size, int weight, bool bold  , bool italic  )
{
	//Relase the previous text, if any
	if(m_text)	m_text->Release();

	if(SUCCEEDED(D3DXCreateFont(device, -size, 0, weight , 0, italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, faceName, &m_text)))
		return true;
	else
		return false;
}

bool Text::Create3DText(LPDIRECT3DDEVICE9 device, char* faceName,int size, int weight /* =100 */, bool bold /* = false */, bool italic /* = false */)
{
	//Release the mesh if previously used 
	if(m_textMesh)	m_textMesh->Release();

	//Create a new world transform at origin
	m_worldTransform = new CWorldTransform;

	//Create a simple cube mesh 
	D3DVERTEXELEMENT9 decl ; 
	D3DXCreateMesh(6, 24, NULL, &decl, device, &m_textMesh);

	HFONT hFont = CreateFont( 0, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana" );

	HDC hdc = CreateCompatibleDC( NULL );

	// Save the old font 
	HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);

	// Create the text mesh 
	//Note you have to specify the text during construction, unlike 2d text rendering
	if ( FAILED( D3DXCreateText( device, hdc, "ishkaran", 0.01f, 0.5f, &m_textMesh, NULL, NULL ) ) ) 
	{

		//Show some error/warning

		// Restore the old font and clean up 
		SelectObject( hdc, hFontOld ); 
		DeleteObject( hFont ); 
		DeleteDC( hdc );

		return false;
	} 
	else
		return true;

}

void Text::Render3D(LPDIRECT3DDEVICE9 device)
{
	//Make sure m_textMesh is valid
	assert(m_textMesh);
	device->SetVertexShaderConstantF( 4, (float*)m_worldTransform->GetTransposedTransform(), 4);
	m_textMesh->DrawSubset( 0 );

}

int Text::Render2D(int xPos, int yPos, int textBoxWidth,int textBoxHeight, DWORD color, char *text,...)
{
	//Make sure m_text is valid
	assert(m_text);
	//First create a rect as a textbox
	RECT tempRect = { xPos, yPos, xPos + textBoxWidth, yPos + textBoxHeight };
	
	va_list list;
	char buff[2048];							//Buffer to hold final output
	size_t size = sizeof(buff);
	ZeroMemory(buff,sizeof(buff));				//0 out the memory

	va_start(list, text);					//Start iterating
	vsnprintf(buff, size - 3, text, list );	//Print into Buffer
	va_end(list);								//Free the memory used by list

	buff[size - 1]	= '\0';							//To keep it null terminated
	buff[size - 2]	= '\n';						//To keep it in Human readable form	
		
	return m_text->DrawTextA(NULL, buff, -1 , &tempRect, FA_LEFT, color );
}

int Text::Render2D(char *text, int xPos, int yPos, int textBoxWidth,int textBoxHeight, DWORD color ,int count, FONTALIGNMENT alignment )
{
	//Make sure m_text is valid
	assert(m_text);
	//First create a rect as a textbox
	RECT tempRect = { xPos, yPos, xPos + textBoxWidth, yPos + textBoxHeight };

	//Create a format 
	DWORD format = DT_EXPANDTABS;


	format |= DT_WORDBREAK;
	switch ( alignment )
	{
	case FA_LEFT:
		format |= DT_LEFT;
		break;
	case FA_CENTER:
		format |= DT_CENTER;
		break;
	case FA_RIGHT:
		format |= DT_RIGHT;
		break;
	case FA_TOPRIGHT:
		format |= DT_RIGHT | DT_TOP;
		break;
	case FA_BOTTOMRIGHT:
		format |= DT_RIGHT | DT_BOTTOM;
		break;
	case FA_TOPLEFT:
		format |= DT_LEFT | DT_TOP;
		break;
	case FA_BOTTOMLEFT:
		format |= DT_LEFT | DT_BOTTOM;
		break;
	}


	return m_text->DrawTextA(NULL, text, count , &tempRect, alignment, color );
}