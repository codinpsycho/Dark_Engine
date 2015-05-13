//.....................................................
//		Dark Engine :: Graphics Manager (Encapsulates rendering of meshes,textures,text etc)
//		Coded by Ishkaran Singh
//		29/Apr/12
//		I Game hard, I Code Harder
//.....................................................

#ifndef GRAPHICS_MANAGER_H_
#define GRAPHICS_MANAGER_H_
#include "DarkDefs.h"

//Forward Declarations
class Text;
class Quad;
class DarkRect;
class CDarkSprite;

namespace DarkEngine
{
	class CGraphicsManager
	{

	public:
		//Our only Instance
		static CGraphicsManager& Instance()
		{
			static CGraphicsManager obj;
			return obj;
		}
	
		~CGraphicsManager(void);
		//All things will be rendered with default Shaders
		bool ShowText(int xPos, int yPos, int width, int height, COLOR color, char *text,...);
		bool ShowTexture(DarkRect& rect_, char *texture/*Path to Texture*/);	//Texture must be present in ResourceManager or a Default texture will be applied
		bool RnderMesh(int xPos, int yPos, char *texture/*Path to Mesh*/);			//Mesh must be present in ResourceManager 
		void SetTextParams(char *font_, int size);

	private:
		CGraphicsManager(void);		//No one can create you :(

		Text *m_text;		//to diaplay text

	};


}

#endif