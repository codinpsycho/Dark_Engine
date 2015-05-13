#include "Camera.h" 
#include "DarkDefs.h"
#include "Dark.h"
#include "CInputManager.h"
using namespace DarkEngine;

CCamera::CCamera(D3DXVECTOR3 cameraPosition_)
{
	m_look.x = 0.0f;
	m_look.y = 0.0f;
	m_look.z = 1.0f;

	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	m_right.x = 1.0f;
	m_right.y = 0.0f;
	m_right.z = 0.0f;
	m_worldTransform = new CWorldTransform;
	m_worldTransform->SetPositionAbs(cameraPosition_.x, cameraPosition_.y, cameraPosition_.z );
	
	m_viewAngle = 45.0f;
	m_farClip = 1000.0f;
	m_nearClip = 1.0f ;

	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;
	
	m_bCameraMoved = true;		//Make it default to False, because all booleans by default are set to true
	D3DXMatrixIdentity( &m_matrixProjection );
	D3DXMatrixIdentity( &m_matrixView );
}
CCamera::~CCamera(void)
{

}
void CCamera::Init()
{
// 	//Set Mouse Cursor positions
// 	POINT *CursorPosition =  EngineManager::Instance()->InputHandler()->GetCursorPosition();
// 	m_mouseX = CursorPosition->x;
// 	m_mouseY = CursorPosition->y;
	//Set camera with default vectors
	D3DXMatrixLookAtLH(&m_matrixView, &m_worldTransform->GetPosition(), &m_look , &m_up);
}

void CCamera::LookAt( float x_, float y_, float z_ )
{
	m_look.x = x_, m_look.y = y_, m_look.z = z_;
	m_bCameraMoved = true;
}

void CCamera::SetUpVector( float x_, float y_, float z_ )
{
	m_up.x = x_, m_up.y = y_, m_up.z = z_;
	m_bCameraMoved = true;
}

void CCamera::SetNearFarClipPlane(float near_, float far_)
{
	m_nearClip = near_;
	m_farClip = far_;
}
void CCamera::SetViewingAngle(float angle_)
{
	m_viewAngle = angle_;
}

void CCamera::SetPosition( float x_, float y_, float z_ )
{
	m_worldTransform->SetPositionAbs(x_, y_, z_);
	m_bCameraMoved = true;
}
void CCamera::SetPosition( D3DXVECTOR3 vec_ )
{
	m_worldTransform->SetPositionAbs(vec_.x, vec_.y, vec_.z); 
	m_bCameraMoved = true;
}

//Main function updates View and Projection Matrices
void CCamera::Update(LPDIRECT3DDEVICE9 device)
{

	UpdateMouse();
	//Set up View matrix i.e camera properties
 	D3DXMatrixLookAtLH(&m_matrixView, &m_worldTransform->GetPosition(), &m_look , &m_up);
	
	
	//Now setup projection matrix
	//Set Projection Matrix
	D3DXMatrixPerspectiveFovLH(
		&m_matrixProjection,
		D3DXToRadian(m_viewAngle),
		RENDER_WINDOW.GetWidth() / RENDER_WINDOW.GetHeight(),
		m_nearClip,
		m_farClip
		);

	D3DXMATRIX vp;
	D3DXMatrixMultiplyTranspose(&vp, &m_matrixView, &m_matrixProjection);	//Multiplies and Transposes View and Projection matrices
	device->SetVertexShaderConstantF(0,(float*)vp, 4);	//ViewProjection matrix is at register 0
	//device->SetVertexShaderConstantF(4, (float*)m_worldTransform->GetTransposedTransform(),4);	//World matrix starts at Register 4

}

//General function to update Position in an arbitrary direction
void CCamera::UpdatePosition(D3DXVECTOR3 dir_, float speed_)
{
	m_look = dir_;
	D3DXVECTOR3 position= m_worldTransform->GetPosition();
	D3DXVECTOR3 LookAtVector = m_look - position;
	D3DXVec3Normalize( &LookAtVector, &LookAtVector);
	position += LookAtVector * speed_;
	m_look += LookAtVector * speed_;
}




void CCamera::MoveForward(float speed_)
{
	D3DXVECTOR3 position= m_worldTransform->GetPosition();
	D3DXVECTOR3 LookAtVector = m_look - position;
	D3DXVec3Normalize( &LookAtVector, &LookAtVector);
	position += LookAtVector * speed_;
	m_look += LookAtVector * speed_;
	m_worldTransform->SetPositionAbs(position.x, position.y, position.z);
}


void CCamera::MoveBackward(float speed_)
{
	D3DXVECTOR3 position= m_worldTransform->GetPosition();
	D3DXVECTOR3 LookAtVector = m_look - position  ;
	D3DXVec3Normalize( &LookAtVector, &LookAtVector);
	position -= LookAtVector * speed_;
	m_look -= LookAtVector * speed_;
	m_worldTransform->SetPositionAbs(position.x, position.y, position.z);
}


void CCamera::MoveRight(float speed_)
{
	D3DXVECTOR3 position= m_worldTransform->GetPosition();
	D3DXVECTOR3 vec_;
	D3DXVECTOR3 LookAtVector = m_look - position;
 	D3DXVec3Normalize( &LookAtVector, &LookAtVector);
	D3DXVec3Cross( &vec_, &LookAtVector, &m_up );
	D3DXVec3Normalize( &vec_, &vec_);
	position -= vec_ * speed_;
	m_look		-= vec_ * speed_;
	m_worldTransform->SetPositionAbs(position.x, position.y, position.z);
	
}


void CCamera::MoveLeft(float speed_)
{
	D3DXVECTOR3 position= m_worldTransform->GetPosition();
	D3DXVECTOR3 vec_;
	D3DXVECTOR3 LookAtVector = m_look - position;
	D3DXVec3Normalize( &LookAtVector, &LookAtVector);
	D3DXVec3Cross( &vec_, &m_up, &LookAtVector );
	D3DXVec3Normalize( &vec_, &vec_);
	position -= vec_ * speed_;
	m_look		-= vec_ * speed_;
	m_worldTransform->SetPositionAbs(position.x, position.y, position.z);
	
}

void CCamera::MoveUp(float speed_)
{
	D3DXVECTOR3 position= m_worldTransform->GetPosition();
	D3DXVECTOR3 vec_ = D3DXVECTOR3(0,1,0) ;
	position += vec_ * speed_;
	m_look		+= vec_ * speed_;
	m_worldTransform->SetPositionAbs(position.x, position.y, position.z);

}

void CCamera::MoveDown(float speed_)
{
	D3DXVECTOR3 position= m_worldTransform->GetPosition();
	D3DXVECTOR3 vec_ = D3DXVECTOR3(0,1,0) ;
	position -= vec_ * speed_;
	m_look		-= vec_ * speed_;
	m_worldTransform->SetPositionAbs(position.x, position.y, position.z);

}


void CCamera::UpdateMouse()
{
	D3DXVECTOR3 position = m_worldTransform->GetPosition();	

	if(INPUT_MANAGER.MouseButtonDown(0))
	{
		
		D3DXVECTOR3 Rightvec, UpVec;
		D3DXVECTOR3 LookAtVector = m_look - position;
 		D3DXVec3Normalize( &LookAtVector, &LookAtVector);
	
		D3DXVec3Cross( &Rightvec, &m_up, &LookAtVector);
		D3DXVec3Normalize( &Rightvec, &Rightvec);
		D3DXVec3Cross( &UpVec, &LookAtVector, &Rightvec);
 		
		
		//D3DXVec3Normalize( &Rightvec, &Rightvec);	
		D3DXVec3Normalize( &UpVec, &UpVec);
		
		position	+= Rightvec * INPUT_MANAGER.MouseDx() * 2.5f;
		position	+= UpVec * INPUT_MANAGER.MouseDy()* 2.5f;

		position	+= LookAtVector * INPUT_MANAGER.MouseDz();
		m_look		+= LookAtVector * INPUT_MANAGER.MouseDz();
	}
	else
	{

		D3DXVECTOR3 Rightvec, UpVec;
		D3DXVECTOR3 LookAtVector = m_look - position;
		D3DXVec3Normalize( &LookAtVector, &LookAtVector);

		D3DXVec3Cross( &Rightvec, &m_up, &LookAtVector);
		D3DXVec3Normalize( &Rightvec, &Rightvec);
		D3DXVec3Cross( &UpVec, &LookAtVector, &Rightvec);


		//D3DXVec3Normalize( &Rightvec, &Rightvec);	
		D3DXVec3Normalize( &UpVec, &UpVec);

		m_look	+= Rightvec * INPUT_MANAGER.MouseDx();
		m_look	-= UpVec * INPUT_MANAGER.MouseDy();

		position	+= LookAtVector * INPUT_MANAGER.MouseDz();
		m_look		+= LookAtVector * INPUT_MANAGER.MouseDz();

	}
}



