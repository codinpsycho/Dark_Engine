#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include "Direct3D.h"
#include "WorldTransform.h"
#include "ICamera.h"

class CWorldTransform;


class CCamera : public ICamera
{
	
public:
	
	CCamera(D3DXVECTOR3 cameraPosition_ = D3DXVECTOR3( 0.0f, 0.0f, -300.0f));
	virtual ~CCamera(void);

	void LookAt( D3DXVECTOR3 vec_ )						{ m_look = vec_;	 }
	void LookAt( float x_, float y_, float z_);
	void SetUpVector( D3DXVECTOR3 vec_ )				{ m_up = vec_;		 }
	void SetUpVector( float x_, float y_, float z_);
	void SetPosition( D3DXVECTOR3 vec_ );
	void SetPosition( float x_, float y_, float z_ );
	void SetYaw(float angle_)							{ m_yaw += angle_; m_bCameraMoved = true;	 }
	void SetPitch(float angle_)							{ m_pitch += angle_; m_bCameraMoved = true;	 }
	void SetRoll(float angle_)							{ m_roll += angle_;	m_bCameraMoved = true;   }
	void Init();
	void Update(LPDIRECT3DDEVICE9 device);
	void SetNearFarClipPlane(float, float);
	void SetViewingAngle(float);
	const D3DMATRIX* GetViewMatrix()		{ return &m_matrixView;       }
	const D3DMATRIX* GetProjectionMatrix()	{ return &m_matrixProjection; }	
	float GetYPosition()		const		{ return m_worldTransform->GetPositionY(); }
	float GetZPosition()		const		{ return m_worldTransform->GetPositionZ(); }
	float GetXPosition()		const		{ return m_worldTransform->GetPositionX(); }
	D3DXVECTOR3 GetPosition()	const		{ return m_worldTransform->GetPosition();  }
	void MoveForward(float speed_);	
	void MoveBackward(float speed_);	
	void MoveInDir(float speed_, D3DXVECTOR3* dir_);
	void MoveRight(float speed_);
	void MoveLeft(float speed_);
	void MoveUp(float speed_);
	void MoveDown(float speed_);
	void UpdatePosition(D3DXVECTOR3 dir_, float speed_);

protected:
	D3DXMATRIX m_matrixView, m_matrixProjection;
	D3DXVECTOR3 m_look, m_up, m_right;
	CWorldTransform* m_worldTransform;
	float m_nearClip, m_farClip;
	float m_viewAngle;
	bool m_bCameraMoved;
	float m_yaw, m_pitch, m_roll;
	void UpdateMouse();
	long m_mouseX, m_mouseY;

};


#endif