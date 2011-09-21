/*!
 * \file ActionBounceMoveTo.cpp
 * \date 2011/09/19 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqin@gmail.com)
 */
#include <action/ActionBounceMoveTo.h>

ActionBounceMoveTo::ActionBounceMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_fCurrTime = 0.0f;
}

ActionBounceMoveTo::~ActionBounceMoveTo()
{
	//TODO:
}

void ActionBounceMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionBounceMoveTo::Update( float dt )
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

IActionBase* ActionBounceMoveTo::Clone()
{
	return new ActionBounceMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionBounceMoveTo::CloneInverse()
{
	return new ActionBounceMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionBounceMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionBounceMoveTo::Tween()
{
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	switch(m_eType)
	{
	case ATT_EASE_IN:
		vPos = (m_vPosEnd - m_vPosStart)  - BounceTween((m_fTime - m_fCurrTime), vPos, (m_vPosEnd - m_vPosStart), m_fTime) + m_vPosStart;
		return vPos;
	case  ATT_EASE_OUT:
		vPos = BounceTween(m_fCurrTime, m_vPosStart, (m_vPosEnd - m_vPosStart), m_fTime);
		return vPos;
	case ATT_EASE_IN_OUT:
		if(m_fCurrTime < (m_fTime / 2.0f))
		{
			vPos = ((m_vPosEnd - m_vPosStart)  - BounceTween((m_fTime - m_fCurrTime * 2.0f), vPos, (m_vPosEnd - m_vPosStart), m_fTime)) * 0.5f + m_vPosStart;
		}
		else
		{
			vPos = BounceTween((m_fCurrTime * 2.0f - m_fTime), vPos, (m_vPosEnd - m_vPosStart), m_fTime) * 0.5f + (m_vPosEnd - m_vPosStart) *0.5f + m_vPosStart;
		}
		return vPos;
	default:
		return vPos;
	}
}

Vector3 ActionBounceMoveTo::BounceTween( float t, const Vector3& b, const Vector3& c, float d )
{
	
	if ((t/=d) < (1/2.75f)) 
	{
		return c *(7.5625f * t * t) + b;
	} else if (t < (2/2.75f)) 
	{
		return c * (7.5625f * (t-=(1.5f / 2.75f)) * t + 0.75f) + b;
	} else if (t < (2.5f / 2.75f))
	{
		return c * (7.5625f * (t-=(2.25f / 2.75f)) * t + 0.9375f) + b;
	} else 
	{
		return c * (7.5625f * (t-=(2.625f / 2.75f)) * t + 0.984375f) + b;
	}
}
