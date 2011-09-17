/*!
 * \file ActionExpoMoveTo.h
 * \date 9-16-2011 22:32:31
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include <action/ActionExpoMoveTo.h>
#include <math.h>
ActionExpoMoveTo::ActionExpoMoveTo( MOVE_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_fCurrTime = 0.0f;
}

ActionExpoMoveTo::~ActionExpoMoveTo()
{
	//TODO:
}

void ActionExpoMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionExpoMoveTo::Update( float dt )
{
	if (! IsRunning()) return;

	m_fCurrTime += dt;

	if( m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}

	SetPosition(Tween());
	
}

IActionBase* ActionExpoMoveTo::Clone()
{
	return new ActionExpoMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionExpoMoveTo::CloneInverse()
{
	return new ActionExpoMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionExpoMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionExpoMoveTo::Tween()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	switch(m_eType)
	{
	case  MOVE__EASEIN:
		if(m_fCurrTime < IMath::FLOAT_MIN)return m_vPosStart;
		alpha = ((m_fCurrTime / m_fTime) - 1.0f) * 10.0f;
		alpha = pow(2.0f, alpha);
		vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return vPos;
	case  MOVE__EASEOUT:
		if((m_fTime - m_fCurrTime) < IMath::FLOAT_MIN) return m_vPosEnd;
		alpha = (m_fCurrTime / m_fTime) * -10.0f;
		alpha = -pow(2.0f, alpha) + 1.0f;
		vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return vPos;
	case  MOVE__EASEINOUT:
		if(m_fCurrTime < IMath::FLOAT_MIN)return m_vPosStart;
		if((m_fTime - m_fCurrTime) < IMath::FLOAT_MIN) return m_vPosEnd;
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if(alpha < 1.0f)
		{
			alpha = (alpha - 1.0f) * 10.0f;
			alpha = pow(2.0f, alpha);
			vPos = (m_vPosEnd - m_vPosStart) / 2.0f * alpha + m_vPosStart;
			return vPos;
		}
		else
		{
			alpha = (alpha - 1.0f) * -10.0f;
			alpha = -pow(2.0f, alpha) + 2.0f;
			vPos = (m_vPosEnd - m_vPosStart) / 2.0f * alpha + m_vPosStart;
		}
		return vPos;
	default:
		return vPos;
	}
}
