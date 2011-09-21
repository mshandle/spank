/*!
 * \file ActionBySpline.cpp
 * \date 2011/08/22 15:40
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionBySpline.h>
#include <math.h>

ActionBySpline::ActionBySpline(float time)
{	
	m_fTime = time;
	
	// Set up matrix
	// Hermite polynomial
	m_matCoeffs.e[Matrix4x4::E11] = 2.0f; //2 -2 1 1
	m_matCoeffs.e[Matrix4x4::E12] = -2.0f;
	m_matCoeffs.e[Matrix4x4::E13] = 1.0f;
	m_matCoeffs.e[Matrix4x4::E14] = 1.0f;

	m_matCoeffs.e[Matrix4x4::E21] = -3.0f;
	m_matCoeffs.e[Matrix4x4::E22] = 3.0f;
	m_matCoeffs.e[Matrix4x4::E23] = -2.0f;
	m_matCoeffs.e[Matrix4x4::E24] = -1.0f;

	m_matCoeffs.e[Matrix4x4::E31] = 0.0f;
	m_matCoeffs.e[Matrix4x4::E32] = 0.0f;
	m_matCoeffs.e[Matrix4x4::E33] = 1.0f;
	m_matCoeffs.e[Matrix4x4::E34] = 0.0f;
	
	m_matCoeffs.e[Matrix4x4::E41] = 1.0f;
	m_matCoeffs.e[Matrix4x4::E42] = 0.0f;
	m_matCoeffs.e[Matrix4x4::E43] = 0.0f;
	m_matCoeffs.e[Matrix4x4::E44] = 0.0f;
	m_bClosed = false;
	Reset();
}

ActionBySpline::~ActionBySpline()
{
	// TODO: 
}

void ActionBySpline::AddPoint(const Vector3& Point)
{
	m_vPoints.push_back(Point);
}

const Vector3& ActionBySpline::GetPoint(uint index)
{
	return m_vPoints[index];
}

uint ActionBySpline::GetNumberPoints() const
{
	return m_vPoints.size();
}

void ActionBySpline::Clear()
{
	m_vPoints.clear();
	m_vTangents.clear();
}

void ActionBySpline::UpdatePoint(uint index, const Vector3 &value)
{
	m_vPoints[index] = value;
	RecalcTangents();
}

Vector3 ActionBySpline::Interpolate(uint fromIndex, float t) const
{
	if((fromIndex + 1) == m_vPoints.size()) return m_vPoints[fromIndex];

	if(t <= 0.0f) return m_vPoints[fromIndex];
	if(t >= 1.0f) return m_vPoints[fromIndex + 1];

	float t2 = t * t;
	float t3 = t2 * t;
	Vector4 powers(t3, t2, t, 1);
	// Algorithm is ret = powers * mCoeffs * Matrix4(point1, point2, tangent1, tangent2)
	//
	const Vector3& point1 = m_vPoints[fromIndex];
	const Vector3& point2 = m_vPoints[fromIndex + 1];
	const Vector3& tan1 = m_vTangents[fromIndex];
	const Vector3& tan2 = m_vTangents[fromIndex + 1];

	Matrix4x4 pt;
	pt.e[Matrix4x4::E11] = point1.x;
	pt.e[Matrix4x4::E12] = point1.y;
	pt.e[Matrix4x4::E13] = point1.z;
	pt.e[Matrix4x4::E14] = 1.0f;

	pt.e[Matrix4x4::E21] = point2.x;
	pt.e[Matrix4x4::E22] = point2.y;
	pt.e[Matrix4x4::E23] = point2.z;
	pt.e[Matrix4x4::E24] = 1.0f;
	
	pt.e[Matrix4x4::E31] = tan1.x;
	pt.e[Matrix4x4::E32] = tan1.y;
	pt.e[Matrix4x4::E33] = tan1.z;
	pt.e[Matrix4x4::E34] = 1.0f;

	pt.e[Matrix4x4::E41] = tan2.x;
	pt.e[Matrix4x4::E42] = tan2.y;
	pt.e[Matrix4x4::E43] = tan2.z;
	pt.e[Matrix4x4::E44] = 1.0f;

	Vector4 ret = powers * m_matCoeffs * pt;

	return Vector3(ret.x, ret.y, ret.z);
}

void ActionBySpline::RecalcTangents(void)
{
	// Catmull-Rom approach
	// tangent[i] = 0.5 * (point[i+1] - point[i-1])
	// Li = 1/2( Pi+1 - Pi-1)

	int numPosints = m_vPoints.size();

	if(numPosints < 2) return;

	if((m_vPoints[0].x == m_vPoints[numPosints - 1].x)
		&&(m_vPoints[0].y == m_vPoints[numPosints - 1].y)
		&&(m_vPoints[0].z == m_vPoints[numPosints - 1].z))
	{
		m_bClosed = true;
	}
	else
	{
		m_bClosed = false;
	}
	
	m_vTangents.resize(numPosints);
	for (int i = 0; i< numPosints; ++i)
	{
		if(i == 0)
		{
			if(m_bClosed)
			{
				m_vTangents[i] = 0.5f * (m_vPoints[1] - m_vPoints[numPosints - 2]);
			}
			else
			{
				m_vTangents[i] = 0.5 * (m_vPoints[1] - m_vPoints[0]);
			}
		}
		else if(i == numPosints-1)
		{
			if (m_bClosed)
			{
				m_vTangents[i] = m_vTangents[0];
			}
			else
			{
				m_vTangents[i] = 0.5f * (m_vPoints[i] - m_vPoints[i-1]);
			}
		}
		else
		{
			m_vTangents[i] = 0.5 * (m_vPoints[i+1] - m_vPoints[i-1]);
		}
	}
}

void ActionBySpline::Reset()
{
	m_fCurrenTime = 0.0f;
	RecalcTangents();
}

void ActionBySpline::Update(float dt)
{
	if(! IsRunning()) return;

	m_fCurrenTime +=dt;
	//action end
	if( m_fCurrenTime > m_fTime)
	{
		SetPosition(m_vPoints[m_vPoints.size() - 1]);
		Stop();
		return;
	}

	float alpha = m_fCurrenTime / m_fTime;
	float fSeg = alpha * (m_vPoints.size() - 1);
	uint segIdx = (uint) fSeg;
	alpha = fSeg - segIdx;

	Vector3 Position = Interpolate(segIdx,alpha);
	Vector3 prvPosition = GetPosition();

	Vector3 direction = Position - prvPosition;
	if(direction.x < IMath::FLOAT_MIN)
	{
		SetPosition(Position);
		return;
	}

	SetPosition(Position);
	float fradian = atanf(direction.y/direction.x);
	SetRotation(Vector3(0.0f, 0.0f, 1.0f), fradian);
}

IActionBase* ActionBySpline::Clone()
{
	ActionBySpline* pActionBySpline = new ActionBySpline(*this);
	pActionBySpline->Reset();
	return pActionBySpline;
}

IActionBase* ActionBySpline::CloneInverse()
{
	ActionBySpline* pActionBySpline = new ActionBySpline(*this);
	pActionBySpline->Clear();
	pActionBySpline->m_vPoints.reserve(m_vPoints.size());
	pActionBySpline->m_vPoints.assign(m_vPoints.rbegin(), m_vPoints.rend());
	pActionBySpline->Reset();
	return pActionBySpline;
}

float ActionBySpline::GetTimeLength() const
{
	return m_fTime;
}
