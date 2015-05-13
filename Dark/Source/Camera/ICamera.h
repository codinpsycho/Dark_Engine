#pragma once



class ICamera
{
public:

	ICamera(void)
	{
	}

	virtual ~ICamera(void)
	{
	}

	virtual void Update(LPDIRECT3DDEVICE9 device_) = 0;
	virtual void UpdatePosition(D3DXVECTOR3 dir_, float speed_) = 0;
};
