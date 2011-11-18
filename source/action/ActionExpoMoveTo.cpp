/*!
 * \file ActionExpoMoveTo.h
 * \date 9-16-2011 22:32:31
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include <action/ActionExpoMoveTo.h>
#include <math.h>
ActionExpoMoveTo::ActionExpoMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
:ActionMoveTo(posStart, posEnd, time)
{
	m_eType = eType;
}

ActionExpoMoveTo::~ActionExpoMoveTo()
{
	//TODO:
}

IActionBase* ActionExpoMoveTo::Clone()
{
	return new ActionExpoMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionExpoMoveTo::CloneInverse()
{
	return new ActionExpoMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionExpoMoveTo::Interpolate()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	switch(m_eType)
	{
	case  ATT_EASE_IN:
		if(m_fCurrTime < IMath::FLOAT_MIN)return 0.0f;;
		alpha = ((m_fCurrTime / m_fTime) - 1.0f) * 10.0f;
		alpha = powf(2.0f, alpha);
		return alpha;
	case  ATT_EASE_OUT:
		if((m_fTime - m_fCurrTime) < IMath::FLOAT_MIN) return 1.0f;
		alpha = (m_fCurrTime / m_fTime) * -10.0f;
		alpha = -powf(2.0f, alpha) + 1.0f;
		return alpha;
	case  ATT_EASE_IN_OUT:
		if(m_fCurrTime < IMath::FLOAT_MIN)return 0.0f;
		if((m_fTime - m_fCurrTime) < IMath::FLOAT_MIN) return 1.0f;
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if(alpha < 1.0f)
		{
			alpha = (alpha - 1.0f) * 10.0f;
			alpha = powf(2.0f, alpha);
			vPos = (m_vPosEnd - m_vPosStart) * 0.5f * alpha + m_vPosStart;
			alpha /= 2.0f;
			alpha *= alpha;
		}
		else
		{
			alpha = (alpha - 1.0f) * -10.0f;
			alpha = -powf(2.0f, alpha) + 2.0f;
			alpha /= 2.0f;
			alpha *= alpha;
		}
		return alpha;
	default:
		return alpha;
	}
}