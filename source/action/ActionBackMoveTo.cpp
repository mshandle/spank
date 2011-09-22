/*!
 * \file ActionBackMove.cpp
 * \date 2011/09/16 14:54
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionBackMoveTo.h>

ActionBackMoveTo::ActionBackMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time ): ActionMoveTo(posStart, posEnd, time)
{
	m_eType = eType;
}

ActionBackMoveTo::~ActionBackMoveTo()
{
	//TODO:
}


IActionBase* ActionBackMoveTo::Clone()
{
	return new ActionBackMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionBackMoveTo::CloneInverse()
{
	return new ActionBackMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionBackMoveTo::Interpolate()
{
	float alpha = 0.0f;
	float  s = 1.70158f;
	switch(m_eType)
	{
	case ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha = alpha * alpha * ((s + 1.0f) * alpha - s);
		return alpha;
	case  ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha = (alpha * alpha * ((s + 1.0f) * alpha +s) + 1.0f);
		return alpha;
	case  ATT_EASE_IN_OUT:
		s *= 1.525f;
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if(alpha < 1.0f)
		{
			alpha = (alpha * alpha * ((s  + 1.0f) * alpha - s));
			alpha /= 2.0f;
		}
		else
		{
			alpha = alpha - 2.0f;
			alpha = (alpha * alpha * ((s + 1.0f) * alpha + s) + 2.0f);
			alpha /= 2.0f;
		}
		return alpha;
	default:
		return alpha;
		break;
	}
}