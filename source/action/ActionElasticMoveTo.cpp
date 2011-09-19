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
	//(m_vPosEnd - m_vPosStart) * (m_fCurrTime / m_fTime) + m_vPosStart
	// c * (t / d) + b;

	//if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
	//if (!a || a < Math.abs(c)) { a=c; var s=p/4; }
	//else var s = p/(2*Math.PI) * Math.asin (c/a);
	//return (a*Math.pow(2,-10*t) * Math.sin( (t*d-s)*(2*Math.PI)/p ) + c + b);

	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	switch(m_eType)
	{
	case ATT_EASE_IN:
		{
			if(m_fCurrTime < IMath::FLOAT_MIN) return m_vPosStart;
			if((m_fTime - m_fCurrTime) < IMath::FLOAT_MIN) return m_vPosEnd;
			float fAtt = m_fTime * 0.4f;
			float fCof = fAtt / 6.0f;
			alpha = m_fCurrTime / m_fTime - 1.0f;
			float alpha1 = powf(2.0f, 10.0f * alpha);
			float alpha2 = (m_fCurrTime * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
			alpha2 = sinf(alpha2);
			vPos = -(m_vPosEnd - m_vPosStart) * alpha1 * alpha2 + m_vPosStart;
			return vPos;
		}
	case ATT_EASE_OUT:
		{
			if( m_fCurrTime < IMath::FLOAT_MIN) return m_vPosStart;
			if((m_fTime - m_fCurrTime) < IMath::FLOAT_MIN) return m_vPosEnd;
			float fAtt = m_fTime * 0.4f;
			float fCof = fAtt / 6.0f;
			alpha = m_fCurrTime / m_fTime;
			float alpha1 = powf(2.0f, -10.0f * alpha);
			float alpha2 = (m_fCurrTime * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
			alpha2 = sinf(alpha2);
			vPos = (m_vPosEnd - m_vPosStart) * alpha1 * alpha2 + m_vPosEnd;
		}
		return vPos;
	case ATT_EASE_IN_OUT:
		{
			if(m_fCurrTime < IMath::FLOAT_MIN) return m_vPosStart;
			if((m_fTime - m_fCurrTime) < IMath::FLOAT_MIN) return m_vPosEnd;
			float fAtt = m_fTime * 0.8f;
			float fCof = fAtt / 0.2f;
			alpha = m_fCurrTime /( m_fTime / 2.0f);
			if( alpha < 1.0f)
			{
				alpha -= 1.0f;
				float alpha1 = powf(2.0f, 10.0f * alpha);
				float alpha2 = (m_fCurrTime * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
				alpha2 = sinf(alpha2);
				vPos = -(m_vPosEnd - m_vPosStart) / 2.0f * alpha1 * alpha2 + m_vPosStart;
			}
			else
			{
				alpha -= 1.0f;
				float alpha1 = powf(2.0f, -10.0f * alpha);
				float alpha2 = (m_fCurrTime * m_fTime - fCof) * (2.0f * IMath::F_PI) / fAtt;
				alpha2 = sinf(alpha2);
				vPos = (m_vPosEnd - m_vPosStart) * alpha1 * alpha2 + m_vPosEnd;
			}
		return vPos;
		}
	default:
		return vPos;
	}
}


