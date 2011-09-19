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
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	//switch(m_eType)
	//{
	//case ATT_EASE_OUT:
	//	{	
	//		alpha = m_fCurrTime / m_fTime;
	//		if(alpha < (1.0f / 2.75f))
	//			vPos = (m_vPosEnd - m_vPosStart) * (7.5625f * alpha *alpha) + m_vPosStart;
	//		else if (alpha < 2.0f / 2.75f)
	//		{
	//			alpha =alpha -  (1.5f / 2.75f);
	//			alpha *= alpha;
	//			alpha = 7.5625f * alpha + 0.75f;
	//			vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
	//		}
	//		else if (alpha < (2.5f / 2.75f))
	//		{
	//			alpha =alpha -  (2.25f / 2.75f);
	//			alpha *= alpha;
	//			alpha = 7.5625f * alpha + 0.9375f;
	//			vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
	//		}
	//		else
	//		{
	//			alpha =alpha -  (2.625f / 2.75f);
	//			alpha *= alpha;
	//			alpha = 7.5625f * alpha + 0.984375f;
	//			vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
	//		}
	//		return vPos;
	//	}
	//case ATT_EASE_IN:
	//	{
	//		alpha = (m_fTime - m_fCurrTime) / m_fTime;
	//		if(alpha < (1.0f / 2.75f))
	//			vPos = (m_vPosEnd - m_vPosStart) - (m_vPosEnd - m_vPosStart) * (7.5625f * alpha *alpha) + m_vPosStart;
	//		else if (alpha < 2.0f / 2.75f)
	//		{
	//			alpha =alpha -  (1.5f / 2.75f);
	//			alpha *= alpha;
	//			alpha = 7.5625f * alpha + 0.75f;
	//			vPos = (m_vPosEnd - m_vPosStart) - (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
	//		}
	//		else if (alpha < (2.5f / 2.75f))
	//		{
	//			alpha =alpha -  (2.25f / 2.75f);
	//			alpha *= alpha;
	//			alpha = 7.5625f * alpha + 0.9375f;
	//			vPos = (m_vPosEnd - m_vPosStart) - (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
	//		}
	//		else
	//		{
	//			alpha =alpha -  (2.625f / 2.75f);
	//			alpha *= alpha;
	//			alpha = 7.5625f * alpha + 0.984375f;
	//			vPos = (m_vPosEnd - m_vPosStart) - (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
	//		}
	//		return vPos;
	//	 }
	//case ATT_EASE_IN_OUT:
	//		if( m_fCurrTime < (m_fTime / 2.0f))
	//		{
	//			alpha = 1.0f - (2.0f * m_fCurrTime) / m_fTime;
	//			if(alpha < (1.0f / 2.75f))
	//				vPos = (m_vPosEnd - m_vPosStart) * (7.5625f * alpha *alpha) * 0.5f + m_vPosStart;
	//			else if (alpha < 2.0f / 2.75f)
	//			{
	//				alpha =alpha -  (1.5f / 2.75f);
	//				alpha *= alpha;
	//				alpha = 7.5625f * alpha + 0.75f;
	//				vPos = (m_vPosEnd - m_vPosStart) * alpha  * 0.5f + m_vPosStart;
	//			}
	//			else if (alpha < (2.5f / 2.75f))
	//			{
	//				alpha =alpha -  (2.25f / 2.75f);
	//				alpha *= alpha;
	//				alpha = 7.5625f * alpha + 0.9375f;
	//				vPos = (m_vPosEnd - m_vPosStart) * alpha * 0.5f + m_vPosStart;
	//			}
	//			else
	//			{
	//				alpha =alpha -  (2.625f / 2.75f);
	//				alpha *= alpha;
	//				alpha = 7.5625f * alpha + 0.984375f;
	//				vPos = (m_vPosEnd - m_vPosStart) * alpha *0.5f + m_vPosStart;
	//			}
	//			return vPos;
	//		}
	//		else
	//		{
	//			alpha = ((m_fCurrTime * 2.0f) - m_fTime) / m_fTime;
	//			if(alpha < (1.0f / 2.75f))
	//				vPos = (m_vPosEnd - m_vPosStart) * (7.5625f * alpha *alpha) * 0.5 + (m_vPosEnd - m_vPosStart) * 0.5f + m_vPosStart;
	//			else if (alpha < 2.0f / 2.75f)
	//			{
	//				alpha =alpha -  (1.5f / 2.75f);
	//				alpha *= alpha;
	//				alpha = 7.5625f * alpha + 0.75f;
	//				vPos = (m_vPosEnd - m_vPosStart) * alpha  * 0.5f + (m_vPosEnd - m_vPosStart) * 0.5f  + m_vPosStart;
	//			}
	//			else if (alpha < (2.5f / 2.75f))
	//			{
	//				alpha =alpha -  (2.25f / 2.75f);
	//				alpha *= alpha;
	//				alpha = 7.5625f * alpha + 0.9375f;
	//				vPos = (m_vPosEnd - m_vPosStart) * alpha * 0.5f +(m_vPosEnd - m_vPosStart) * 0.5f + m_vPosStart;
	//			}
	//			else
	//			{
	//				alpha =alpha -  (2.625f / 2.75f);
	//				alpha *= alpha;
	//				alpha = 7.5625f * alpha + 0.984375f;
	//				vPos = (m_vPosEnd - m_vPosStart) * alpha *0.5f + (m_vPosEnd - m_vPosStart) * 0.5 + m_vPosStart;
	//			}
	//			return vPos;
	//		}
	//	return vPos;
	//default:
	//	return vPos;
	//}
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

Vector3 ActionBounceMoveTo::BounceTween( float t, Vector3& b, Vector3& c, float d )
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
