/*!
 * \file ActionCircMoveTo
 * \date 2011/9/17 17:25
 *
 *
 * \author wbaoqing(wbaoqing@gmail.com)
 */

#include <action/ActionCircMoveTo.h>
#include <math.h>
ActionCircMoveTo::ActionCircMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd =  posEnd;
	m_fTime = time;
	m_fCurrTime = 0.0f;
}

ActionCircMoveTo::~ActionCircMoveTo()
{
	//TODO:
}

void ActionCircMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionCircMoveTo::Update( float dt )
{
	if(!IsRunning()) return;

	m_fCurrTime += dt;

	if(m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}

	SetPosition(Tween());

}

IActionBase* ActionCircMoveTo::Clone()
{
	return new ActionCircMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionCircMoveTo::CloneInverse()
{
	return new ActionCircMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionCircMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionCircMoveTo::Tween()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	switch(m_eType)
	{
	case ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha *= alpha;
		alpha = sqrtf(1.0f - alpha);
		vPos = -(m_vPosEnd - m_vPosStart) * (alpha - 1.0f) + m_vPosStart;
		return vPos;
	case ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha *= alpha;
		alpha = sqrtf(1.0f - alpha);
		vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return vPos;
	case ATT_EASE_IN_OUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if(alpha < 1.0f)
		{
			alpha = sqrtf(1.0f - alpha * alpha) - 1.0f;
			vPos = -(m_vPosEnd - m_vPosStart) / 2.0f * alpha + m_vPosStart;
			return vPos;
		}
		else
		{
			alpha -= 2.0f;
			alpha *= alpha;
			alpha = sqrtf(1.0f - alpha) + 1.0f;
			vPos = (m_vPosEnd - m_vPosStart) / 2.0f * alpha + m_vPosStart;
		}
		return vPos;
	default:
		return vPos;
	}
}
