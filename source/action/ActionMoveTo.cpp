/*!
 * \file ActionMoveTo.cpp
 * \date 8-16-2011 12:29:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <action/ActionMoveTo.h>

ActionMoveTo::ActionMoveTo(const Vector3& posStart, const Vector3& posEnd, float time)
{
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;

	Reset();
}

ActionMoveTo::~ActionMoveTo()
{
	// TODO: 
}

void ActionMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionMoveTo::Update(float dt)
{
	if (!IsRunning()) return;

	m_fCurrTime += dt;

	// action end
	if (m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}

	// changing the position
	float alpha = Interpolate(m_fCurrTime / m_fTime);
	SetPosition(m_vPosStart*(1.0f-alpha) + m_vPosEnd*alpha);
}

IActionBase* ActionMoveTo::Clone()
{
	return new ActionMoveTo(m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionMoveTo::CloneInverse()
{
	return new ActionMoveTo(m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionMoveTo::GetTimeLength() const
{
	return m_fTime;
}

float ActionMoveTo::Interpolate(float alpha)
{
	return alpha;
}
