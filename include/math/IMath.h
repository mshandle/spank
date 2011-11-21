/*!
 * \file IMath.h
 * \date 7-25-2011 12:46:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMATH_H__
#define __IMATH_H__

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

class IMath
{
public:
	static float ToRadian(float fDegree);
	static float ToDegree(float fRadian);
	
	static float Random();
	static float Random(float min, float max);

	static void BuildZeroMatrix(Matrix2x2& matOut);
	static void BuildZeroMatrix(Matrix3x3& matOut);
	static void BuildZeroMatrix(Matrix4x4& matOut);

	static void BuildIdentityMatrix(Matrix2x2& matOut);
	static void BuildIdentityMatrix(Matrix3x3& matOut);
	static void BuildIdentityMatrix(Matrix4x4& matOut);

	static void BuildTranslateMatrix(Matrix3x3& matOut, const Vector2& v);
	static void BuildTranslateMatrix(Matrix3x3& matOut, float x, float y);
	static void BuildTranslateMatrix(Matrix4x4& matOut, const Vector3& v);
	static void BuildTranslateMatrix(Matrix4x4& matOut, float x, float y, float z);

	static void BuildScaleMatrix(Matrix3x3& matOut, const Vector3& v);
	static void BuildScaleMatrix(Matrix3x3& matOut, float x, float y, float z);
	static void BuildScaleMatrix(Matrix4x4& matOut, const Vector3& v);
	static void BuildScaleMatrix(Matrix4x4& matOut, float x, float y, float z);

	static void BuildRotateMatrixX(Matrix3x3& matOut, float fRadian);
	static void BuildRotateMatrixX(Matrix4x4& matOut, float fRadian);

	static void BuildRotateMatrixY(Matrix3x3& matOut, float fRadian);
	static void BuildRotateMatrixY(Matrix4x4& matOut, float fRadian);

	static void BuildRotateMatrixZ(Matrix3x3& matOut, float fRadian);
	static void BuildRotateMatrixZ(Matrix4x4& matOut, float fRadian);

	static void BuildRotateMatrix(Matrix3x3& matOut, const Vector3& vx, const Vector3& vy, const Vector3& vz);
	static void BuildRotateMatrix(Matrix4x4& matOut, const Vector3& vx, const Vector3& vy, const Vector3& vz);
	static void BuildRotateMatrix(Matrix3x3& matOut, const Quaternion& q);
	static void BuildRotateMatrix(Matrix4x4& matOut, const Quaternion& q);

	static void BuildOrthoMatrix(Matrix4x4& matOut, float left, float right, float bottom, float top, float near, float far);
	static void BuildFrustumMatrix(Matrix4x4& matOut, float left, float right, float bottom, float top, float near, float far);

public:
	static const float F_PI;
	static const float F_PI2;
	static const float FLOAT_MIN;
	static const float FLOAT_MAX;

	static const Vector2 VEC2_ZERO;
	static const Vector3 VEC3_ZERO;
	static const Vector4 VEC4_ZERO;

	static const Vector2 VEC2_ONE;
	static const Vector3 VEC3_ONE;
	static const Vector4 VEC4_ONE;

	static const Vector2 VEC2_MIN;
	static const Vector3 VEC3_MIN;
	static const Vector4 VEC4_MIN;

	static const Vector2 VEC2_MAX;
	static const Vector3 VEC3_MAX;
	static const Vector4 VEC4_MAX;

	static const Vector3 VEC3_AXISX;
	static const Vector3 VEC3_AXISY;
	static const Vector3 VEC3_AXISZ;

	static const Matrix2x2 MAT2X2_ZERO;
	static const Matrix3x3 MAT3X3_ZERO;
	static const Matrix4x4 MAT4X4_ZERO;

	static const Matrix2x2 MAT2X2_IDENTITY;
	static const Matrix3x3 MAT3X3_IDENTITY;
	static const Matrix4x4 MAT4X4_IDENTITY;

	static const Quaternion ROT_ZERO;

};
#endif // __IMATH_H__
