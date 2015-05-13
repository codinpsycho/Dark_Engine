#pragma once



class IScene
{
public:

	virtual bool Initialize() = 0;
	virtual bool Update(float dt) = 0;
	virtual bool Render() = 0;

	virtual bool Release() = 0;
	IScene()	{}
	virtual ~IScene()	{}
protected:
	
	
};
