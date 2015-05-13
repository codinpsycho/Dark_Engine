#pragma once

#include "IScene.h"

class CDefaultDarkScene : public IScene
{
public:
	CDefaultDarkScene(void);
	virtual ~CDefaultDarkScene(void);

	bool Initialize();
	bool Update(float dt);
	bool Render();
	bool Release();

};
