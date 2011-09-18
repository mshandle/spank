/*!
 * \file IRenderer2D.h
 * \date 7-25-2011 10:31:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRENDERER2D_H__
#define __IRENDERER2D_H__

#include "ISingleton.h"
#include "IShader.h"
#include "math/IMath.h"

class IRenderer2D : public ISingleton
{
public:
	DECLARE_RTTI(IRenderer2D, ISingleton);

	static IRenderer2D& GetInstance();

	virtual void SetModelViewMatrix(const Matrix4x4& mat) = 0;
	virtual const Matrix4x4& GetModelViewMatrix() const = 0;

	virtual void SetProjectionMatrix(const Matrix4x4& mat) = 0;
	virtual const Matrix4x4& GetProjectionMatrix() const = 0;

	virtual const Matrix4x4& GetFinalMatrix() = 0;
	virtual const Matrix4x4& GetFinalMatrixTranspose() = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;

	virtual void DrawPoints(const void* pVerts, uint nNumVerts, IShader* pShader) = 0;
	virtual void DrawLineList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader) = 0;
	virtual void DrawTriangleList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader) = 0;
	virtual void DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader) = 0;

	virtual void DrawRect(float x, float y, float width, float height, IShader* pShader) = 0;

	/*!
	 * \brief the points order is showing below
	 * 
	 *     v1---------v3
	 *     |  \       |
	 *     |     \    |
	 *     |        \ |
	 *     v0---------v2
	 *
	 * two triangles: t1(v0, v1, v2) and t1(v1, v3, v2)
	 *
	 * \param quadVerts
	 * \return 
	 */
	virtual void DrawRect(const QUAD_VERT_POS_UV& quadVerts, IShader* pShader) = 0;
	virtual void DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece, IShader* pShader) = 0;
	virtual void DrawRect(float x, float y, float width, float height, const IMAGE_PIECE* pImagePiece, IShader* pShader) = 0;

	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos) = 0;
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y) = 0;
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos, const Vector2& size) = 0;
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y, float width, float height) = 0;

};
#endif // __IRENDERER2D_H__
