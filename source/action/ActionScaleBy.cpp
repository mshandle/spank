/*!
 * \file ActionScaleBy.cpp
 * \date 8-22-2011 11:10:08
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include <action/ActionScaleBy.h>

ActionScaleBy::ActionScaleBy(const Vector3& ScaleStart, const Vector3& ScaleOff, float time)
{
	m_vScaleStart = ScaleStart;
	m_vScaleOff = ScaleOff;
	m_fTime = time;

	Reset();
}

ActionScaleBy::~ActionScaleBy()
{
	//TODO:
}

void ActionScaleBy::Reset()
{
	m_fTime = 0.0f;
}

void ActionScaleBy::Update(float dt)
{
	if(!IsRunning()) return;

	m_fCurrTime += dt;
	//action end
	if(m_fCurrTime > m_fTime)
	{
		SetScale(Vector3(m_vScaleStart.x * m_vScaleOff.x, m_vScaleStart.y * m_vScaleOff.y, m_vScaleStart.z * m_vScaleOff.z));
		Stop();
		return;
	}

//	float alpha = m_fCurrTime / m_fTime;
//	//TODO:
}

IActionBase* ActionScaleBy::Clone()
{
	return new ActionScaleBy(m_vScaleStart, m_vScaleOff, m_fTime);
}

IActionBase* ActionScaleBy::CloneInverse() 
{
	return new ActionScaleBy(Vector3(m_vScaleStart.x * m_vScaleOff.x, m_vScaleStart.y * m_vScaleOff.y, m_vScaleStart.z * m_vScaleOff.z) ,
							 Vector3(1.0f / m_vScaleOff.x, 1.0f / m_vScaleOff.y, 1.0f / m_vScaleOff.z), 
							 m_fTime);
	
}

float ActionScaleBy::GetTimeLength() const
{
	return m_fTime;
}
