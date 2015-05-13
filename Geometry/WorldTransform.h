#pragma once
#include "Direct3D.h"

//"Abs" stands for Absolute
//"Rel" stands for RelativeS

class CWorldTransform
{

public:
	CWorldTransform(void);
	virtual ~CWorldTransform(void);


	void ClearAll();
	void ClearTranslate();
	void ClearRotate();
	void ClearScale();
	//Set Accessor Functions
	void SetScaleAbs(float x_, float y_, float z_);
	void SetRoatationAbs(float x_, float y_, float z_);
	void SetPositionAbs(float x_, float y_, float z_);
	void SetScaleRel(float x_, float y_, float z_);
	void SetRoatationRel(float x_, float y_, float z_);
	void SetPositionRel(float x_, float y_, float z_);
	void SetWorldTransform(CWorldTransform* worldTransform_)
	{		m_matrixRotate = *(worldTransform_->GetRotationMatrix()); 
			m_matrixScale = *(worldTransform_->GetScaleMatrix());
			m_matrixTranslate = *(worldTransform_->GetPositionMatrix());
	}
	//Get Acessor Functions
	D3DXMATRIX* GetTransform();
	D3DXMATRIX* GetTransposedTransform();
	D3DXVECTOR3 GetPosition()	{ return D3DXVECTOR3(m_matrixTranslate._41,m_matrixTranslate._42,m_matrixTranslate._43); }
	float GetPositionX()		{ return m_matrixTranslate._41; }
	float GetPositionY()		{ return m_matrixTranslate._42; }
	float GetPositionZ()		{ return m_matrixTranslate._43; }
	D3DXMATRIX* GetRotationMatrix()		{ return &m_matrixRotate;		}
	D3DXMATRIX* GetScaleMatrix()		{ return &m_matrixScale;		}
	D3DXMATRIX* GetPositionMatrix()	{ return &m_matrixTranslate;	}
	float GetScaleX()			{ return m_matrixScale._11;     }
	float GetScaleY()			{ return m_matrixScale._22;     }
	float GetScaleZ()			{ return m_matrixScale._33;     }
	float GetRotationX()		{ return m_rotationX;           }
	float GetRotationY()		{ return m_rotationY;           }
	float GetRotationZ()		{ return m_rotationZ;           }


protected:
	D3DXMATRIX m_matrixRotate, m_matrixTranslate, m_matrixScale, m_matrixTransform;
	float m_rotationX, m_rotationY, m_rotationZ;		//Only values for rotation is stored because rest can be enterd directly

};
