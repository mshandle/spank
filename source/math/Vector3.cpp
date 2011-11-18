/*!
 * \file Vector3.cpp
 * \date 7-25-2011 14:01:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Vector3.h>
#include <math/IMath.h>
#include <math.h>

Vector3::Vector3()
{
	// TODO: 
}

Vector3::Vector3(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
	// TODO: 
}

float Vector3::Length() const
{
	return sqrtf(x*x+y*y+z*z);
}

bool Vector3::Normalize()
{
	float fMag = sqrtf(x*x+y*y+z*z);
	if (fMag <= IMath::FLOAT_MIN) fMag = 0.0f;
	float fInvMag = 1.0f / fMag;		// if fMag == 0.0f, must crush here

	x *= fInvMag;
	y *= fInvMag;
	z *= fInvMag;

	return true;
}

Vector3& Vector3::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return (*this);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return (*this);
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return (*this);
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return (*this);
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

float operator*(const Vector3& v1, const Vector3& v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

Vector3 operator*(float s, const Vector3& v)
{
	return Vector3(v.x*s, v.y*s, v.z*s);
}

Vector3 operator*(const Vector3& v, float s)
{
	return Vector3(v.x*s, v.y*s, v.z*s);
}

Vector3 operator^(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y*v2.z-v1.z*v2.y, -v1.x*v2.z+v1.z*v2.x, v1.x*v2.y-v1.y*v2.x);
}
