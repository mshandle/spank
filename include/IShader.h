/*!
 * \file IShader.h
 * \date 7-25-2011 9:54:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISHADER_H__
#define __ISHADER_H__

#include "IObject.h"
#include "ITexture.h"
#include "VertexAttribute.h"
#include "math/Matrix4x4.h"

class IShader : public IObject
{
public:
	DECLARE_RTTI(IShader, IObject);

	/*!
	 * \brief set matrix
	 *
	 * if the matrix is order like following:
	 *     [ 0  4  8  12 ]
	 *     [ 1  5  9  13 ]
	 *     [ 2  6  10 14 ]
	 *     [ 3  7  11 15 ]
	 * after pass it into shader, the matrix in the shader should be:
	 *     [ 0  1  2  3  ]
	 *     [ 4  5  6  7  ]
	 *     [ 8  9  10 11 ]
	 *     [ 12 13 14 15 ]
	 * \param pszParamName
	 * \param m
	 * \return 
	 */
	virtual bool SetMatrix4x4(const char* pszParamName, const Matrix4x4& m) = 0;
	virtual bool SetVector4(const char* pszParamName, const Vector4& v) = 0;
	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture, uint nIndex = 0) = 0;

	virtual const VertexAttribute* GetVertexAttribute() const = 0;
	virtual void Reset() = 0;
	virtual bool Commit(const void* pVerts) = 0;

protected:
	IShader() {};
	virtual ~IShader() {};

};

#endif // __ISHADER_H__
