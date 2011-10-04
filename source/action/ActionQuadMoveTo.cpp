/*!
 * \file ActionQuadraticMove.cpp
 * \date 2011/09/16 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuadMoveTo.h>

ActionQuadMoveTo::ActionQuadMoveTo(ACTION_TWEEN_TYPE eType, const Vector3& posStart, const Vector3& posEnd, float time )
:ActionMoveTo(posStart, posEnd, time)
{
	m_eType = eType;
}
ActionQuadMoveTo::~ActionQuadMoveTo()
{
	//TODO:
}

IActionBase* ActionQuadMoveTo::Clone()
{
	return new ActionQuadMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuadMoveTo::CloneInverse()
{
	return new ActionQuadMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}


float ActionQuadMoveTo::Interpolate()
{
	float alpha = 0.0f;

	switch (m_eType)
	{
	case ATT_EASE_IN:
		alpha = m_fCurrTime / m_fTime;
		alpha *= alpha;
		return alpha;
	case ATT_EASE_OUT:
		alpha = m_fCurrTime / m_fTime;
		alpha = alpha * (alpha - 2.0f);
		alpha = -alpha;
		return alpha;
	case ATT_EASE_IN_OUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f) ;
		if(alpha < 1.0f)
		{
			alpha = alpha *alpha;
			alpha /= 2.0f;
			alpha *= alpha;
		}
		else
		{	
			alpha = ((alpha - 1.0f) * (alpha - 3.0f) - 1.0f);
			alpha /= -2.0f;
			alpha *= alpha; 
		}
		return alpha;
	default:
		return alpha;
	}
}
