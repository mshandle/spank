/*!
 * \file ActionQuadraticMove.cpp
 * \date 2011/09/16 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuadMoveTo.h>

ActionQuadMoveTo::ActionQuadMoveTo(ACTION_TWEEN_TYPE eType, const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_eType = eType;
	Reset();
}
ActionQuadMoveTo::~ActionQuadMoveTo()
{
	//TODO:
}

void ActionQuadMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionQuadMoveTo::Update( float dt )
{
	if(! IsRunning()) return;
	
	m_fCurrTime += dt;
	// action end;
	if(m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}
	//
	SetPosition(Tween());
}

IActionBase* ActionQuadMoveTo::Clone()
{
	return new ActionQuadMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuadMoveTo::CloneInverse()
{
	return new ActionQuadMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionQuadMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionQuadMoveTo::Tween()
{
	Vector3 pos(0.0f, 0.0f, 0.0f);
	float alpha = 0.0f;

	switch (m_eType)
	{
	case ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha *= alpha;
		pos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return pos;
	case ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime;
		alpha = alpha * (alpha - 2.0f);
		pos = -(m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return pos;
	case ATT_EASE_IN_OUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f) ;
		if(alpha < 1.0f)
		{
			alpha = alpha *alpha;
			pos = (m_vPosEnd - m_vPosStart) / 2.0f * alpha + m_vPosStart;
		}
		else
		{	alpha = ((alpha - 1.0f) * (alpha - 3.0f) - 1.0f);
			pos =  - ((m_vPosEnd - m_vPosStart) / 2.0f )* alpha + m_vPosStart;
		}
		return pos;
	default:
		return pos;
	}
}

