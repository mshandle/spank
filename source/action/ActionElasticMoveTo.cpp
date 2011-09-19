/*!
 * \file ActionElasticMoveTo.cpp
 * \date 2011/09/19 9:32
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionElasticMoveTo.h>
#include <math.h>
ActionElasticMoveTo::ActionElasticMoveTo( ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time)
{
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_fCurrTime = 0.0f;

}
ActionElasticMoveTo::~ActionElasticMoveTo()
{
	//TODO:
}

void ActionElasticMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionElasticMoveTo::Update( float dt )
{
	if(!IsRunning()) return;

	m_fCurrTime += dt;

	if (m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}

	SetPosition(Tween());
}

IActionBase* ActionElasticMoveTo::Clone()
{
	return new ActionElasticMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionElasticMoveTo::CloneInverse()
{
	return new ActionElasticMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionElasticMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionElasticMoveTo::Tween()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	switch(m_eType)
	{
	case ATT_EASE_IN:
		{
			float fAtt = m_fTime * 0.3f;
			float fCof = fAtt / 4.0f;
			alpha = m_fCurrTime / m_fTime - 1.0f;
			float alpha1 = powf(2.0f, 10.0f * alpha);
			float alpha2 = (m_fCurrTime * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
			alpha2 = sinf(alpha2);
			vPos = -(m_vPosEnd - m_vPosStart) * alpha1 * alpha2 + m_vPosStart;
			return vPos;
		}
	case ATT_EASE_OUT:
		{
			float fAtt = m_fTime * 0.3f;
			float fCof = fAtt / 4.0f;
			alpha = m_fCurrTime / m_fTime;
			float alpha1 = powf(2.0f, -10.0f * alpha);
			float alpha2 = (m_fCurrTime * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
			alpha2 = sinf(alpha2);
			vPos = (m_vPosEnd - m_vPosStart) * alpha1 * alpha2 + m_vPosEnd;
		}
		return vPos;
	case ATT_EASE_IN_OUT:
		{
			float fAtt = m_fTime * 0.45f;
			float fCof = fAtt / 4.0f;
			alpha = m_fCurrTime /(m_fTime / 2.0f);

			if( alpha < 1.0f)
			{
				alpha -= 1.0f;
				float alpha1 = powf(2.0f, 10.0f * alpha);
				float alpha2 = (alpha * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
				alpha2 = sinf(alpha2);
				vPos = -0.5f * (m_vPosEnd - m_vPosStart)  * alpha1 * alpha2 + m_vPosStart;
			}
			else
			{
				alpha -= 1.0f;
				float alpha1 = powf(2.0f, -10.0f * alpha);
				float alpha2 = (alpha * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
				alpha2 = sinf(alpha2);
				vPos = (m_vPosEnd - m_vPosStart) * 0.5f * alpha1 * alpha2 + m_vPosEnd;
			}
		return vPos;
		}
	default:
		return vPos;
	}
}


