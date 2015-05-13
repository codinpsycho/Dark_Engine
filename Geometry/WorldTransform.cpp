#include "WorldTransform.h"

CWorldTransform::CWorldTransform(void)
{
	ClearAll();
	m_rotationX = m_rotationY = m_rotationZ = 0.0f;
}

CWorldTransform::~CWorldTransform(void)
{
	
}
//Clears all matrices to identity matrix
void CWorldTransform::ClearAll()
{
	D3DXMatrixIdentity( &m_matrixRotate	   );
	D3DXMatrixIdentity( &m_matrixScale	   );
	D3DXMatrixIdentity( &m_matrixTranslate );
	D3DXMatrixIdentity( &m_matrixTransform );

}

//Clears rotation matrix and also rotation variables
void  CWorldTransform::ClearRotate()
{
	D3DXMatrixIdentity( &m_matrixRotate );
	

}

void CWorldTransform::ClearScale()
{
	D3DXMatrixIdentity( &m_matrixScale );
}

void CWorldTransform::ClearTranslate()
{
	D3DXMatrixIdentity( &m_matrixTranslate );
}

void  CWorldTransform::SetRoatationAbs(float x_, float y_, float z_)
{
	m_rotationX = x_, m_rotationY = y_, m_rotationZ = z_;
	D3DXMatrixRotationYawPitchRoll( &m_matrixRotate, m_rotationY, m_rotationX, m_rotationZ );

}

void  CWorldTransform::SetRoatationRel(float x_, float y_, float z_)
{
	m_rotationX += x_, m_rotationY += y_, m_rotationZ += z_;
	D3DXMatrixRotationYawPitchRoll( &m_matrixRotate, m_rotationY, m_rotationX, m_rotationZ );
	
}

void CWorldTransform::SetScaleAbs(float x_, float y_, float z_)
{
	m_matrixScale._11 = x_;
	m_matrixScale._22 = y_;
	m_matrixScale._33 = z_;
}

void CWorldTransform::SetScaleRel(float x_, float y_, float z_)
{
	m_matrixScale._11 += x_;
	m_matrixScale._22 += y_;
	m_matrixScale._33 += z_;
}

void CWorldTransform::SetPositionAbs(float x_, float y_, float z_)
{
	m_matrixTranslate._41 = x_;
	m_matrixTranslate._42 = y_;
	m_matrixTranslate._43 = z_;

}

void CWorldTransform::SetPositionRel(float x_, float y_, float z_)
{
	m_matrixTranslate._41 += x_;
	m_matrixTranslate._42 += y_;
	m_matrixTranslate._43 += z_;

}

 D3DXMATRIX* CWorldTransform::GetTransform()
{
	m_matrixTransform = m_matrixScale  *  m_matrixRotate * m_matrixTranslate ;
	return &m_matrixTransform;
}


 D3DXMATRIX* CWorldTransform::GetTransposedTransform()
 {
	 //create 3 new matrices for transformation
	 D3DXMATRIX scale,translate,rotate;
	 //transpose all matrices
	 D3DXMatrixTranspose(&scale, &m_matrixScale);
	 D3DXMatrixTranspose(&translate, &m_matrixTranslate);
	 D3DXMatrixTranspose(&rotate, &m_matrixRotate);

	 m_matrixTransform = scale *  rotate * translate ;
	 return &m_matrixTransform;
 }











