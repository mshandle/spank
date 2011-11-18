/*!
 * \file Vector3.h
 * \date 7-25-2011 14:01:49
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3
{
public:
	Vector3();
	Vector3(const Vector3& v);
	Vector3(float x, float y, float z);
	~Vector3();

	float Length() const;
	bool Normalize();

	Vector3& operator=(const Vector3& v);
	Vector3 operator-() const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);

public:
	float x;
	float y;
	float z;
};

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
float operator*(const Vector3& v1, const Vector3& v2);

Vector3 operator*(float s, const Vector3& v);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator^(const Vector3& v1, const Vector3& v2);

#endif // __VECTOR3_H__
