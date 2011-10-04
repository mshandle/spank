/*!
 * \file ActionQuartMoveTo.cpp
 * \date 2011/09/16 17:35
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuartMoveTo.h>

ActionQuartMoveTo::ActionQuartMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
: ActionMoveTo(posStart, posEnd, time)
{
	m_eType = eType;
}

ActionQuartMoveTo::~ActionQuartMoveTo()
{
	//TODO:
}

IActionBase* ActionQuartMoveTo::Clone()
{
	return new ActionQuartMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuartMoveTo::CloneInverse()
{
	return new ActionQuartMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionQuartMoveTo::Interpolate()
{
	float alpha = 0.0f;

	switch(m_eType)
	{
	case ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha =alpha * alpha *alpha *alpha;
		return alpha;
	case  ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha = alpha * alpha * alpha * alpha - 1.0f;
		alpha *= alpha;
		return alpha;
	case  ATT_EASE_IN_OUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if( alpha < 1.0f)
		{
			alpha = alpha * alpha * alpha * alpha;
			alpha /= 2.0f;
			alpha *= alpha;
		}
		else
		{
			alpha -=2.0f;
			alpha = alpha * alpha * alpha * alpha - 2.0f;
			alpha /= -2.0f;
			alpha *= alpha;
		}
		return alpha;
	default:
		return alpha;
	}
}

