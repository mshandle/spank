/*!
 * \file ActionSineMoveTo.h
 * \date 9-16-2011 22:32:32
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include <action/ActionSineMoveTo.h>
#include <math.h>
ActionSineMoveTo::ActionSineMoveTo( MOVE_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_fCurrTime = 0.0f;
}

ActionSineMoveTo::~ActionSineMoveTo()
{
	//TODO:
}

void ActionSineMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionSineMoveTo::Update( float dt )
{
	if(! IsRunning()) return;

	m_fCurrTime += dt;
	if(m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}

	SetPosition(Tween());
}

IActionBase* ActionSineMoveTo::Clone()
{
	return new ActionSineMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionSineMoveTo::CloneInverse()
{
	return new ActionSineMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionSineMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionSineMoveTo::Tween()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	switch(m_eType)
	{
	case  MOVE__EASEIN:
		alpha = m_fCurrTime / m_fTime;
		alpha = cos( alpha * IMath::F_PI / 2.0f);
		vPos = - (m_vPosEnd - m_vPosStart) * alpha + m_vPosEnd;
		return vPos;
	case  MOVE__EASEOUT:
		alpha = m_fCurrTime / m_fTime;
		alpha = sin( alpha * IMath::F_PI / 2.0f);
		vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return vPos;
	case  MOVE__EASEINOUT:
		alpha = m_fCurrTime / m_fTime;
		alpha = cos( alpha * IMath::F_PI) - 1.0f;
		vPos = -(m_vPosEnd - m_vPosStart) / 2.0f * alpha + m_vPosStart;
		return vPos;
	default:
		return vPos;
	}
}
