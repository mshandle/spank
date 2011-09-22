/*!
 * \file ActionCubicMove.cpp
 * \date 2011/09/16 16:50
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionCubicMoveTo.h>

ActionCubicMoveTo::ActionCubicMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time ): ActionMoveTo(posStart, posEnd, time)
{
	m_eType = eType;
}

ActionCubicMoveTo::~ActionCubicMoveTo()
{
	//TODO:
}

IActionBase* ActionCubicMoveTo::Clone()
{
	return new ActionCubicMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);;
}

IActionBase* ActionCubicMoveTo::CloneInverse()
{
	return new ActionCubicMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}


float ActionCubicMoveTo::Interpolate()
{
	float alpha = 0.0f;
	switch(m_eType)
	{
	case ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha = alpha * alpha *alpha;
		return alpha;
	case ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha =alpha * alpha * alpha + 1.0f;
		return alpha;
	case  ATT_EASE_IN_OUT:
		alpha = m_fCurrTime /(m_fTime /2.0f);
		if( alpha < 1.0f)
		{
			alpha = alpha * alpha * alpha;
			alpha /= 2.0f;
		}
		else
		{
			alpha -= 2.0f;
			alpha = alpha * alpha * alpha + 2.0f;
			alpha /= 2.0f;
		}
		return alpha;
	default:
		return alpha;
	}
}