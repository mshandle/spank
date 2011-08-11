/*!
 * \file Matrix2x2.cpp
 * \date 08-08-2011 22:08:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Matrix2x2.h>
#include <math/IMath.h>
#include <math.h>

Matrix2x2::Matrix2x2()
{
	// TODO: 
}

Matrix2x2::Matrix2x2(const Matrix2x2& m)
{
	e[E11] = m.e[E11]; e[E12] = m.e[E12];
	e[E21] = m.e[E21]; e[E22] = m.e[E22];
}

Matrix2x2::Matrix2x2(float e11, float e12,
					 float e21, float e22)
{
	e[E11] = e11; e[E12] = e12;
	e[E21] = e21; e[E22] = e22;
}

Matrix2x2::~Matrix2x2()
{
	// TODO: 
}

Matrix2x2& Matrix2x2::operator=(const Matrix2x2& m)
{
	e[E11] = m.e[E11]; e[E12] = m.e[E12];
	e[E21] = m.e[E21]; e[E22] = m.e[E22];
	return (*this);
}

Matrix2x2& Matrix2x2::Scale(const Vector2& v)
{
	//
	// [ *x    N/E ]
	// [ N/E   *y  ]
	//
	e[E11] *= v.x;
	e[E22] *= v.y;
	return (*this);
}

Matrix2x2& Matrix2x2::Scale(float x, float y)
{
	//
	// [ *x    N/E ]
	// [ N/E   *y  ]
	//
	e[E11] *= x;
	e[E22] *= y;
	return (*this);
}

Matrix2x2& Matrix2x2::Transport()
{
	float temp = 0.0f;

	temp = e[E12]; e[E12] = e[E21]; e[E21] = temp;

	return (*this);
}

float Matrix2x2::Det()
{
	//������ʽ
	return e[E11]*e[E22] - e[E12]*e[E21];
}

bool Matrix2x2::Invert()
{
	//������ʽ
	float fDet = e[E11]*e[E22] - e[E12]*e[E21];
	if (fabsf(fDet) <= IMath::FLOAT_MIN) fDet = 0.0f;
	float fInvDet = 1.0f / fDet;		// can be crush here, if fDet == 0.0f

	//�������
	Matrix2x2 matAdjoint;
	matAdjoint.e[E11] =  e[E22];
	matAdjoint.e[E12] = -e[E21];
	matAdjoint.e[E21] = -e[E12];
	matAdjoint.e[E22] =  e[E11];

	e[E11] = matAdjoint.e[E11] * fInvDet;
	e[E12] = matAdjoint.e[E12] * fInvDet;
	e[E21] = matAdjoint.e[E21] * fInvDet;
	e[E22] = matAdjoint.e[E22] * fInvDet;

	return true;
}

Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& m)
{
	// ������A��B�ĳ˻�����C�ĵ�i�е�j�е�Ԫ��c(ij)����A�ĵ�i����B�ĵ�j�еĶ�ӦԪ�س˻��ĺ͡�����ʵ����ѧ�ֲᣬ��ѧ�����磬�ڶ��棩
	Matrix2x2 result;
	result.e[E11] = e[E11]*m.e[E11] + e[E12]*m.e[E21];
	result.e[E12] = e[E11]*m.e[E12] + e[E12]*m.e[E22];
	result.e[E21] = e[E21]*m.e[E11] + e[E22]*m.e[E21];
	result.e[E22] = e[E21]*m.e[E12] + e[E22]*m.e[E22];

	(*this) = result;
	return (*this);
}

Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& m)
{
	e[E11] += m.e[E11]; e[E12] += m.e[E12];
	e[E21] += m.e[E21]; e[E22] += m.e[E22];
	return (*this);
}

Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& m)
{
	e[E11] -= m.e[E11]; e[E12] -= m.e[E12];
	e[E21] -= m.e[E21]; e[E22] -= m.e[E22];
	return (*this);
}

Matrix2x2 operator*(const Matrix2x2& m1, const Matrix2x2& m2)
{
	Matrix2x2 result;

	result.e[Matrix2x2::E11] = m1.e[Matrix2x2::E11]*m2.e[Matrix2x2::E11] + m1.e[Matrix2x2::E12]*m2.e[Matrix2x2::E21];
	result.e[Matrix2x2::E12] = m1.e[Matrix2x2::E11]*m2.e[Matrix2x2::E12] + m1.e[Matrix2x2::E12]*m2.e[Matrix2x2::E22];
	result.e[Matrix2x2::E21] = m1.e[Matrix2x2::E21]*m2.e[Matrix2x2::E11] + m1.e[Matrix2x2::E22]*m2.e[Matrix2x2::E21];
	result.e[Matrix2x2::E22] = m1.e[Matrix2x2::E21]*m2.e[Matrix2x2::E12] + m1.e[Matrix2x2::E22]*m2.e[Matrix2x2::E22];

	return result;
}

Matrix2x2 operator+(const Matrix2x2& m1, const Matrix2x2& m2)
{
	Matrix2x2 result;

	result.e[Matrix2x2::E11] = m1.e[Matrix2x2::E11] + m2.e[Matrix2x2::E11];
	result.e[Matrix2x2::E12] = m1.e[Matrix2x2::E12] + m2.e[Matrix2x2::E12];
	result.e[Matrix2x2::E21] = m1.e[Matrix2x2::E21] + m2.e[Matrix2x2::E21];
	result.e[Matrix2x2::E22] = m1.e[Matrix2x2::E22] + m2.e[Matrix2x2::E22];

	return result;
}

Matrix2x2 operator-(const Matrix2x2& m1, const Matrix2x2& m2)
{
	Matrix2x2 result;

	result.e[Matrix2x2::E11] = m1.e[Matrix2x2::E11] - m2.e[Matrix2x2::E11];
	result.e[Matrix2x2::E12] = m1.e[Matrix2x2::E12] - m2.e[Matrix2x2::E12];
	result.e[Matrix2x2::E21] = m1.e[Matrix2x2::E21] - m2.e[Matrix2x2::E21];
	result.e[Matrix2x2::E22] = m1.e[Matrix2x2::E22] - m2.e[Matrix2x2::E22];

	return result;
}

Vector2 operator*(const Matrix2x2& m, const Vector2& v)
{
	Vector2 result;

	result.x = m.e[Matrix2x2::E11]* v.x + m.e[Matrix2x2::E12]* v.y;
	result.y = m.e[Matrix2x2::E21]* v.x + m.e[Matrix2x2::E22]* v.y;

	return result;
}
