/*!
 * \file ActionQuintMoveTo.cpp
 * \date 2011/09/16 17:53
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuintMoveTo.h>

ActionQuintMoveTo::ActionQuintMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
: ActionMoveTo(posStart, posEnd, time)
{
	m_eType = eType;
}

ActionQuintMoveTo::~ActionQuintMoveTo()
{
	//TODO:
}

IActionBase* ActionQuintMoveTo::Clone()
{
	return new ActionQuintMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuintMoveTo::CloneInverse()
{
	return new ActionQuintMoveTo (m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionQuintMoveTo::Interpolate()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	//TODO:
	switch(m_eType)
	{
	case  ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha = alpha * alpha * alpha * alpha * alpha;
		return alpha;
	case  ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha = alpha * alpha * alpha * alpha * alpha + 1.0f;
		return alpha;
	case  ATT_EASE_IN_OUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if(alpha < 1.0f)
		{
			alpha = alpha * alpha * alpha * alpha * alpha;
			vPos = (m_vPosEnd - m_vPosStart) * 0.5f * alpha + m_vPosStart;
			alpha /= 2.0f;
			alpha *= alpha;
		}
		else
		{
			alpha -=2;
			alpha = alpha * alpha * alpha * alpha * alpha + 2.0f;
			alpha /= 2.0f;
			alpha *= alpha;
		}
		return alpha;
	default:
		return alpha;
	}
}