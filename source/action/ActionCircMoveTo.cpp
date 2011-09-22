/*!
 * \file ActionCircMoveTo
 * \date 2011/9/17 17:25
 *
 *
 * \author wbaoqing(wbaoqing@gmail.com)
 */

#include <action/ActionCircMoveTo.h>
#include <math.h>
ActionCircMoveTo::ActionCircMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time ): ActionMoveTo(posStart, posEnd, time)
{
	m_eType = eType;
}

ActionCircMoveTo::~ActionCircMoveTo()
{
	//TODO:
}

IActionBase* ActionCircMoveTo::Clone()
{
	return new ActionCircMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionCircMoveTo::CloneInverse()
{
	return new ActionCircMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}


float ActionCircMoveTo::Interpolate()
{
	float alpha = 0.0f;
	switch(m_eType)
	{
	case ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha *= alpha;
		alpha = sqrtf(1.0f - alpha);
		alpha = (alpha - 1.0f);
		alpha = -alpha;
		return alpha;
	case ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha *= alpha;
		alpha = sqrtf(1.0f - alpha);
		return alpha;
	case ATT_EASE_IN_OUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if(alpha < 1.0f)
		{
			alpha = sqrtf(1.0f - alpha * alpha) - 1.0f;
			alpha /= 2.0f;
			alpha = -alpha;
		}
		else
		{
			alpha -= 2.0f;
			alpha *= alpha;
			alpha = sqrtf(1.0f - alpha) + 1.0f;
			alpha /= 2.0f; 
		}
		return alpha;
	default:
		return alpha;
	}
}