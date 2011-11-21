/*!
 * \file IMath.cpp
 * \date 7-25-2011 12:46:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/IMath.h>
#include <math.h>
#include <stdlib.h>

const float IMath::F_PI = 3.141592f;
const float IMath::F_PI2 = 6.283184f;

const float IMath::FLOAT_MIN = 0.000001f;
const float IMath::FLOAT_MAX = 3.402823466e+38F;

const Vector2 IMath::VEC2_ZERO(0.0f, 0.0f);
const Vector3 IMath::VEC3_ZERO(0.0f, 0.0f, 0.0f);
const Vector4 IMath::VEC4_ZERO(0.0f, 0.0f, 0.0f, 0.0f);

const Vector2 IMath::VEC2_ONE(1.0f, 1.0f);
const Vector3 IMath::VEC3_ONE(1.0f, 1.0f, 1.0f);
const Vector4 IMath::VEC4_ONE(1.0f, 1.0f, 1.0f, 1.0f);

const Vector2 IMath::VEC2_MIN(-IMath::FLOAT_MAX, -IMath::FLOAT_MAX);
const Vector3 IMath::VEC3_MIN(-IMath::FLOAT_MAX, -IMath::FLOAT_MAX, -IMath::FLOAT_MAX);
const Vector4 IMath::VEC4_MIN(-IMath::FLOAT_MAX, -IMath::FLOAT_MAX, -IMath::FLOAT_MAX, -IMath::FLOAT_MAX);

const Vector2 IMath::VEC2_MAX(IMath::FLOAT_MAX, IMath::FLOAT_MAX);
const Vector3 IMath::VEC3_MAX(IMath::FLOAT_MAX, IMath::FLOAT_MAX, IMath::FLOAT_MAX);
const Vector4 IMath::VEC4_MAX(IMath::FLOAT_MAX, IMath::FLOAT_MAX, IMath::FLOAT_MAX, IMath::FLOAT_MAX);

const Vector3 IMath::VEC3_AXISX(1.0f, 0.0f, 0.0f);
const Vector3 IMath::VEC3_AXISY(0.0f, 1.0f, 0.0f);
const Vector3 IMath::VEC3_AXISZ(0.0f, 0.0f, 1.0f);

const Matrix2x2 IMath::MAT2X2_ZERO(0.0f, 0.0f, 
								   0.0f, 0.0f);
const Matrix3x3 IMath::MAT3X3_ZERO(0.0f, 0.0f, 0.0f, 
								   0.0f, 0.0f, 0.0f, 
								   0.0f, 0.0f, 0.0f);
const Matrix4x4 IMath::MAT4X4_ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f);

const Matrix2x2 IMath::MAT2X2_IDENTITY(1.0f, 0.0f, 
									   0.0f, 1.0f);
const Matrix3x3 IMath::MAT3X3_IDENTITY(1.0f, 0.0f, 0.0f, 
									   0.0f, 1.0f, 0.0f, 
									   0.0f, 0.0f, 1.0f);
const Matrix4x4 IMath::MAT4X4_IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

const Quaternion IMath::ROT_ZERO(0.0f, 0.0f, 0.0f, 1.0f);

float IMath::ToRadian(float fDegree)
{
	return fDegree / 180.0f * F_PI;
}

float IMath::ToDegree(float fRadian)
{
	return fRadian / F_PI * 180.0f;
}

float IMath::Random()
{
	return ((float)(rand()%RAND_MAX) / RAND_MAX);
}

float IMath::Random(float min, float max)
{
	return min + (Random()*(max-min));
}

void IMath::BuildZeroMatrix(Matrix2x2& matOut)
{
	//
	// [ 0   0 ]
	// [ 0   0 ]
	//
	matOut.e[Matrix2x2::E11] = 0.0f; matOut.e[Matrix2x2::E12] = 0.0f;
	matOut.e[Matrix2x2::E21] = 0.0f; matOut.e[Matrix2x2::E22] = 0.0f;
}

void IMath::BuildZeroMatrix(Matrix3x3& matOut)
{
	//
	// [ 0   0   0 ]
	// [ 0   0   0 ]
	// [ 0   0   0 ]
	//
	matOut.e[Matrix3x3::E11] = 0.0f; matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = 0.0f; matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = 0.0f;
}

void IMath::BuildZeroMatrix(Matrix4x4& matOut)
{
	//
	// [ 0   0   0   0 ]
	// [ 0   0   0   0 ]
	// [ 0   0   0   0 ]
	// [ 0   0   0   0 ]
	//
	matOut.e[Matrix4x4::E11] = 0.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 0.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 0.0f; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 0.0f;
}

void IMath::BuildIdentityMatrix(Matrix2x2& matOut)
{
	//
	// [ 1   0 ]
	// [ 0   1 ]
	//
	matOut.e[Matrix2x2::E11] = 1.0f; matOut.e[Matrix2x2::E12] = 0.0f;
	matOut.e[Matrix2x2::E21] = 0.0f; matOut.e[Matrix2x2::E22] = 1.0f;
}

void IMath::BuildIdentityMatrix(Matrix3x3& matOut)
{
	//
	// [ 1   0   0 ]
	// [ 0   1   0 ]
	// [ 0   0   1 ]
	//
	matOut.e[Matrix3x3::E11] = 1.0f; matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = 1.0f; matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = 1.0f;
}

void IMath::BuildIdentityMatrix(Matrix4x4& matOut)
{
	//
	// [ 1   0   0   0 ]
	// [ 0   1   0   0 ]
	// [ 0   0   1   0 ]
	// [ 0   0   0   1 ]
	//
	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildTranslateMatrix(Matrix3x3& matOut, const Vector2& v)
{
	//
	// [ 1  0  x ]
	// [ 0  1  y ]
	// [ 0  0  1 ]
	//
	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = v.x;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = v.y;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f;
}

void IMath::BuildTranslateMatrix(Matrix3x3& matOut, float x, float y)
{
	//
	// [ 1  0  x ]
	// [ 0  1  y ]
	// [ 0  0  1 ]
	//
	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = x;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = y;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f;
}

void IMath::BuildTranslateMatrix(Matrix4x4& matOut, const Vector3& v)
{
	//
	// [ 1  0  0  x ]
	// [ 0  1  0  y ]
	// [ 0  0  1  z ]
	// [ 0  0  0  1 ]
	//
	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = v.x;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = v.y;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f; matOut.e[Matrix4x4::E34] = v.z;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildTranslateMatrix(Matrix4x4& matOut, float x, float y, float z)
{
	//
	// [ 1  0  0  x ]
	// [ 0  1  0  y ]
	// [ 0  0  1  z ]
	// [ 0  0  0  1 ]
	//
	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = x;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = y;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f; matOut.e[Matrix4x4::E34] = z;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}


void IMath::BuildScaleMatrix(Matrix3x3& matOut, const Vector3& v)
{
	//
	// [ x  0  0 ]
	// [ 0  y  0 ]
	// [ 0  0  z ]
	//
	matOut.e[Matrix4x4::E11] = v.x;  matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = v.y;  matOut.e[Matrix4x4::E23] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = v.z;
}

void IMath::BuildScaleMatrix(Matrix3x3& matOut, float x, float y, float z)
{
	//
	// [ x  0  0 ]
	// [ 0  y  0 ]
	// [ 0  0  z ]
	//
	matOut.e[Matrix4x4::E11] = x;    matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = y;    matOut.e[Matrix4x4::E23] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = z;
}

void IMath::BuildScaleMatrix(Matrix4x4& matOut, const Vector3& v)
{
	//
	// [ x  0  0  0 ]
	// [ 0  y  0  0 ]
	// [ 0  0  z  0 ]
	// [ 0  0  0  1 ]
	//
	matOut.e[Matrix4x4::E11] = v.x;  matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = v.y;  matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = v.z;  matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildScaleMatrix(Matrix4x4& matOut, float x, float y, float z)
{
	//
	// [ x  0  0  0 ]
	// [ 0  y  0  0 ]
	// [ 0  0  z  0 ]
	// [ 0  0  0  1 ]
	//
	matOut.e[Matrix4x4::E11] = x;    matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = y;    matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = z;    matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrixX(Matrix3x3& matOut, float fRadian)
{
	//
	// [ 1     0        0    ]
	// [ 0   cos(r)  -sin(r) ]
	// [ 0   sin(r)   cos(r) ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix3x3::E11] = 1.0f; matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = cr;   matOut.e[Matrix3x3::E23] =-sr;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = sr;   matOut.e[Matrix3x3::E33] = cr;
}

void IMath::BuildRotateMatrixX(Matrix4x4& matOut, float fRadian)
{
	//
	// [ 1     0        0     0 ]
	// [ 0   cos(r)  -sin(r)  0 ]
	// [ 0   sin(r)   cos(r)  0 ]
	// [ 0     0        0     1 ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = cr;   matOut.e[Matrix4x4::E23] =-sr;   matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = sr;   matOut.e[Matrix4x4::E33] = cr;   matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrixY(Matrix3x3& matOut, float fRadian)
{
	//
	// [  cos(r)   0   sin(r) ]
	// [    0      1     0    ]
	// [ -sin(r)   0   cos(r) ]
	//
	float cr = cosf(fRadian);
	float sr = cosf(fRadian);

	matOut.e[Matrix3x3::E11] = cr;   matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = sr;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = 1.0f; matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] =-sr;   matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = cr;
}

void IMath::BuildRotateMatrixY(Matrix4x4& matOut, float fRadian)
{
	//
	//[  cos(r)  0  sin(r)   0 ]
	//[    0     1    0      0 ]
	//[ -sin(r)  0  cos(r)   0 ]
	//[    0     0    0      1 ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix4x4::E11] = cr;   matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = sr;   matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] =-sr;   matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = cr;   matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrixZ(Matrix3x3& matOut, float fRadian)
{
	//
	// [ cos(r)  -sin(r)  0 ]
	// [ sin(r)   cos(r)  0 ]
	// [   0        0     1 ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix3x3::E11] = cr;   matOut.e[Matrix3x3::E12] =-sr;   matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = sr;   matOut.e[Matrix3x3::E22] = cr;   matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = 1.0f;
}

void IMath::BuildRotateMatrixZ(Matrix4x4& matOut, float fRadian)
{
	// 
	// [ cos(r)  -sin(r)  0  0 ]
	// [ sin(r)   cos(r)  0  0 ]
	// [   0        0     1  0 ]
	// [   0        0     0  1 ]
	// 
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix4x4::E11] = cr;   matOut.e[Matrix4x4::E12] =-sr;   matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = sr;   matOut.e[Matrix4x4::E22] = cr;   matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrix(Matrix3x3& matOut, const Vector3& vx, const Vector3& vy, const Vector3& vz)
{
	//
	// [ vx.x  vy.x  vz.x ]
	// [ vx.y  vy.y  vz.y ]
	// [ vx.z  vy.z  vz.z ]
	//
	matOut.e[Matrix3x3::E11] = vx.x; matOut.e[Matrix3x3::E12] = vy.x; matOut.e[Matrix3x3::E13] = vz.x;
	matOut.e[Matrix3x3::E21] = vx.y; matOut.e[Matrix3x3::E22] = vy.y; matOut.e[Matrix3x3::E23] = vz.y;
	matOut.e[Matrix3x3::E31] = vx.z; matOut.e[Matrix3x3::E32] = vy.z; matOut.e[Matrix3x3::E33] = vz.z;
}

void IMath::BuildRotateMatrix(Matrix4x4& matOut, const Vector3& vx, const Vector3& vy, const Vector3& vz)
{
	//
	// [ vx.x  vy.x  vz.x  0 ]
	// [ vx.y  vy.y  vz.y  0 ]
	// [ vx.z  vy.z  vz.z  0 ]
	// [  0     0     0    1 ]
	//
	matOut.e[Matrix4x4::E11] = vx.x; matOut.e[Matrix4x4::E12] = vy.x; matOut.e[Matrix4x4::E13] = vz.x; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = vx.y; matOut.e[Matrix4x4::E22] = vy.y; matOut.e[Matrix4x4::E23] = vz.y; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = vx.z; matOut.e[Matrix4x4::E32] = vy.z; matOut.e[Matrix4x4::E33] = vz.z; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrix(Matrix3x3& matOut, const Quaternion& q)
{
	// 
	// [ 1-2*y*y-2*z*z   2*x*y-2*z*w    2*x*z+2*y*w  ]
	// [  2*x*y+2*z*w   1-2*x*x-2*z*z   2*y*z-2*x*w  ]
	// [  2*x*z-2*y*w    2*y*z+2*x*w   1-2*x*x-2*y*y ]
	// 
	float f2WX = 2.0f*q.w*q.x;
	float f2WY = 2.0f*q.w*q.y;
	float f2WZ = 2.0f*q.w*q.z;
	float f2XX = 2.0f*q.x*q.x;
	float f2XY = 2.0f*q.x*q.y;
	float f2XZ = 2.0f*q.x*q.z;
	float f2YY = 2.0f*q.y*q.y;
	float f2YZ = 2.0f*q.y*q.z;
	float f2ZZ = 2.0f*q.z*q.z;

	matOut.e[Matrix3x3::E11] = 1.0f - f2YY - f2ZZ;
	matOut.e[Matrix3x3::E12] = f2XY - f2WZ;
	matOut.e[Matrix3x3::E13] = f2XZ + f2WY;

	matOut.e[Matrix3x3::E21] = f2XY + f2WZ;
	matOut.e[Matrix3x3::E22] = 1.0f - f2XX - f2ZZ;
	matOut.e[Matrix3x3::E23] = f2YZ - f2WX;

	matOut.e[Matrix3x3::E31] = f2XZ - f2WY;
	matOut.e[Matrix3x3::E32] = f2YZ + f2WX;
	matOut.e[Matrix3x3::E33] = 1.0f - f2XX - f2YY;
}

void IMath::BuildRotateMatrix(Matrix4x4& matOut, const Quaternion& q)
{
	// 
	// [ 1-2*y*y-2*z*z   2*x*y-2*z*w    2*x*z+2*y*w   0 ]
	// [  2*x*y+2*z*w   1-2*x*x-2*z*z   2*y*z-2*x*w   0 ]
	// [  2*x*z-2*y*w    2*y*z+2*x*w   1-2*x*x-2*y*y  0 ]
	// [       0              0              0        1 ]
	// 
	float f2WX = 2.0f*q.w*q.x;
	float f2WY = 2.0f*q.w*q.y;
	float f2WZ = 2.0f*q.w*q.z;
	float f2XX = 2.0f*q.x*q.x;
	float f2XY = 2.0f*q.x*q.y;
	float f2XZ = 2.0f*q.x*q.z;
	float f2YY = 2.0f*q.y*q.y;
	float f2YZ = 2.0f*q.y*q.z;
	float f2ZZ = 2.0f*q.z*q.z;

	matOut.e[Matrix4x4::E11] = 1.0f - f2YY - f2ZZ;
	matOut.e[Matrix4x4::E12] = f2XY - f2WZ;
	matOut.e[Matrix4x4::E13] = f2XZ + f2WY;
	matOut.e[Matrix4x4::E14] = 0.0f;

	matOut.e[Matrix4x4::E21] = f2XY + f2WZ;
	matOut.e[Matrix4x4::E22] = 1.0f - f2XX - f2ZZ;
	matOut.e[Matrix4x4::E23] = f2YZ - f2WX;
	matOut.e[Matrix4x4::E24] = 0.0f;

	matOut.e[Matrix4x4::E31] = f2XZ - f2WY;
	matOut.e[Matrix4x4::E32] = f2YZ + f2WX;
	matOut.e[Matrix4x4::E33] = 1.0f - f2XX - f2YY;
	matOut.e[Matrix4x4::E34] = 0.0f;

	matOut.e[Matrix4x4::E41] = 0.0f;
	matOut.e[Matrix4x4::E42] = 0.0f;
	matOut.e[Matrix4x4::E43] = 0.0f;
	matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildOrthoMatrix(Matrix4x4& matOut, float left, float right, float bottom, float top, float near, float far)
{
	// 
	// [        2/(right-left)                    0                         0            0 ]
	// [              0                    2/(top-bottom)                   0            0 ]
	// [              0                           0                  -2/(far-near)       0 ]
	// [ -(right+left)/(right-left)  -(top+bottom)/(top-bottom)  -(far+near)/(far-near)  1 ]
	// 
	matOut.e[Matrix4x4::E11] = 2.0f/(right - left);
	matOut.e[Matrix4x4::E12] = 0.0f;
	matOut.e[Matrix4x4::E13] = 0.0f;
	matOut.e[Matrix4x4::E14] = 0.0f;

	matOut.e[Matrix4x4::E21] = 0.0f;
	matOut.e[Matrix4x4::E22] = 2.0f/(top - bottom);
	matOut.e[Matrix4x4::E23] = 0.0f;
	matOut.e[Matrix4x4::E24] = 0.0f;

	matOut.e[Matrix4x4::E31] = 0.0f;
	matOut.e[Matrix4x4::E32] = 0.0f;
	matOut.e[Matrix4x4::E33] = -2.0f/(far - near);
	matOut.e[Matrix4x4::E34] = 0.0f;

	matOut.e[Matrix4x4::E41] = -(right + left)/(right - left);
	matOut.e[Matrix4x4::E42] = -(top + bottom)/(top - bottom);
	matOut.e[Matrix4x4::E43] = -(far + near)/(far - near);
	matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildFrustumMatrix(Matrix4x4& matOut, float left, float right, float bottom, float top, float near, float far)
{
	// 
	// [    2*near/(right-left)                0                         0              0 ]
	// [           0                   2*near/(top-bottom)               0              0 ]
	// [ (right+left)/(right-left)  (top+bottom)/(top-bottom)  -(far+near)/(far-near)  -1 ]
	// [           0                           0               -2*far*near/(far-near)   0 ]
	// 
	matOut.e[Matrix4x4::E11] = 2.0f*near/(right - left);
	matOut.e[Matrix4x4::E12] = 0.0f;
	matOut.e[Matrix4x4::E13] = 0.0f;
	matOut.e[Matrix4x4::E14] = 0.0f;

	matOut.e[Matrix4x4::E21] = 0.0f;
	matOut.e[Matrix4x4::E22] = 2.0f*near/(top - bottom);
	matOut.e[Matrix4x4::E23] = 0.0f;
	matOut.e[Matrix4x4::E24] = 0.0f;

	matOut.e[Matrix4x4::E31] = (right+left)/(right-left);
	matOut.e[Matrix4x4::E32] = (top+bottom)/(top-bottom);
	matOut.e[Matrix4x4::E33] = -(far+near)/(far-near);
	matOut.e[Matrix4x4::E34] = -1.0f;

	matOut.e[Matrix4x4::E41] = 0.0f;
	matOut.e[Matrix4x4::E42] = 0.0f;
	matOut.e[Matrix4x4::E43] = -2*far*near/(far-near);
	matOut.e[Matrix4x4::E44] = 0.0f;
}
