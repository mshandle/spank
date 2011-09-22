/*!
 * \file Renderer2D_Impl.cpp
 * \date 7-25-2011 10:45:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Renderer2D_Impl.h"
#include <BaseTypeEx.h>
#include <IRenderDevice.h>
#include <IShaderMgr.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <GLES2/gl2.h>
#include <math.h>

IRenderer2D& IRenderer2D::GetInstance()
{
	static Renderer2D_Impl s_Renderer2D_Impl;
	return s_Renderer2D_Impl;
}

Renderer2D_Impl::Renderer2D_Impl()
{
	m_bNeedUpdateFinalMatrix = true;
}

Renderer2D_Impl::~Renderer2D_Impl()
{
	// TODO: 
}

bool Renderer2D_Impl::Initialize()
{
	m_matModelView = IMath::MAT4X4_IDENTITY;

	float fSurfaceWidth = (float)IRenderDevice::GetInstance().GetSurfaceWidth();
	float fSurfaceHeight = (float)IRenderDevice::GetInstance().GetSurfaceHeight();
	IMath::BuildOrthoMatrix(m_matProj, -fSurfaceWidth/2.0f, fSurfaceWidth/2.0f, -fSurfaceHeight/2.0f, fSurfaceHeight/2.0f, 0.1f, 1000.0f);

	float fDegree = ScreenUtil::GetInstance().GetRotationDegree();
	if (fabsf(fDegree - 0.0f) > IMath::FLOAT_MIN)
	{
		// setup the rotation matrix to rotate world
		Matrix4x4 matRot;
		IMath::BuildRotateMatrixZ(matRot, IMath::ToRadian(fDegree));
		m_matProj *= matRot;
	}

	UpdateFinalMatrix();

	return true;
}

void Renderer2D_Impl::Terminate()
{
	// TODO: 
}

void Renderer2D_Impl::SetModelViewMatrix(const Matrix4x4& mat)
{
	m_matModelView = mat;
	m_bNeedUpdateFinalMatrix = true;
}

const Matrix4x4& Renderer2D_Impl::GetModelViewMatrix() const
{
	return m_matModelView;
}

void Renderer2D_Impl::SetProjectionMatrix(const Matrix4x4& mat)
{
	m_matProj = mat;
	m_bNeedUpdateFinalMatrix = true;
}

const Matrix4x4& Renderer2D_Impl::GetProjectionMatrix() const
{
	return m_matProj;
}

const Matrix4x4& Renderer2D_Impl::GetFinalMatrix()
{
	if (m_bNeedUpdateFinalMatrix) UpdateFinalMatrix();
	return m_matModelViewProj;
}

const Matrix4x4& Renderer2D_Impl::GetFinalMatrixTranspose()
{
	if (m_bNeedUpdateFinalMatrix) UpdateFinalMatrix();
	return m_matModelViewProjTranspose;
}

void Renderer2D_Impl::BeginRender()
{
	SetModelViewMatrix(IMath::MAT4X4_IDENTITY);
}

void Renderer2D_Impl::EndRender()
{
	// TODO: 
}

// void Renderer2D_Impl::DrawPoints(const void* pVerts, uint nNumVerts, IShader* pShader)
// {
// 	if(!pShader) return;
// 
// 	pShader->Commit(pVerts);
// 	glDrawArrays(GL_POINTS, 0, nNumVerts);
// }
// 
// void Renderer2D_Impl::DrawLineList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader)
// {
// 	if(!pShader) return;
// 
// 	pShader->Commit(pVerts);
// // 	glLineWidth(2.0f);
// 	glDrawElements(GL_LINES, nNumIndis, GL_UNSIGNED_SHORT, pIndis);
// }

void Renderer2D_Impl::DrawTriangleList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader)
{
	if (!pShader) return;

	pShader->Commit(pVerts);
	glDrawElements(GL_TRIANGLES, nNumIndis, GL_UNSIGNED_SHORT, pIndis);

	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glDrawElements error code: 0x%04x", eError);
}

void Renderer2D_Impl::DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader)
{
	if (!pShader) return;

	pShader->Commit(pVerts);
	glDrawElements(GL_TRIANGLE_STRIP, nNumIndis, GL_UNSIGNED_SHORT, pIndis);

	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glDrawElements error code: 0x%04x", eError);
}

void Renderer2D_Impl::DrawRect(float x, float y, float width, float height, IShader* pShader)
{
	static VATTR_POS_UV s_Verts[4] =
	{
		{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f},
		{-0.5f, +0.5f, 0.0f, 0.0f, 1.0f},
		{+0.5f, -0.5f, 0.0f, 1.0f, 0.0f},
		{+0.5f, +0.5f, 0.0f, 1.0f, 1.0f},
	};

	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};

	float halfWidth = width*0.5f;
	float halfHeight = height*0.5f;

	s_Verts[0].x = x - halfWidth;
	s_Verts[0].y = y - halfHeight;
	s_Verts[1].x = x - halfWidth;
	s_Verts[1].y = y + halfHeight;
	s_Verts[2].x = x + halfWidth;
	s_Verts[2].y = y - halfHeight;
	s_Verts[3].x = x + halfWidth;
	s_Verts[3].y = y + halfHeight;

	DrawTriangleList(s_Verts, 4, s_Indis, 6, pShader);
}

void Renderer2D_Impl::DrawRect(const QUAD_VERT_POS_UV& quadVerts, IShader* pShader)
{
	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};

	DrawTriangleList(&quadVerts.verts[0], 4, s_Indis, 6, pShader);
}

void Renderer2D_Impl::DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece, IShader* pShader)
{
	DrawRect(x, y, pImagePiece->width, pImagePiece->height, pImagePiece, pShader);
}

void Renderer2D_Impl::DrawRect(float x, float y, float width, float height, const IMAGE_PIECE* pImagePiece, IShader* pShader)
{
	static VATTR_POS_UV s_Verts[4] =
	{
		{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f},
		{-0.5f, +0.5f, 0.0f, 0.0f, 1.0f},
		{+0.5f, -0.5f, 0.0f, 1.0f, 0.0f},
		{+0.5f, +0.5f, 0.0f, 1.0f, 1.0f},
	};

	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};

	float halfWidth = width*0.5f;
	float halfHeight = height*0.5f;

	s_Verts[0].x = x - halfWidth;
	s_Verts[0].y = y - halfHeight;
	s_Verts[0].u = pImagePiece->u;
	s_Verts[0].v = pImagePiece->v;

	s_Verts[1].x = x - halfWidth;
	s_Verts[1].y = y + halfHeight;
	s_Verts[1].u = pImagePiece->u;
	s_Verts[1].v = pImagePiece->v + pImagePiece->dv;

	s_Verts[2].x = x + halfWidth;
	s_Verts[2].y = y - halfHeight;
	s_Verts[2].u = pImagePiece->u + pImagePiece->du;
	s_Verts[2].v = pImagePiece->v;

	s_Verts[3].x = x + halfWidth;
	s_Verts[3].y = y + halfHeight;
	s_Verts[3].u = pImagePiece->u + pImagePiece->du;
	s_Verts[3].v = pImagePiece->v + pImagePiece->dv;

	DrawTriangleList(s_Verts, 4, s_Indis, 6, pShader);
}

bool Renderer2D_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos)
{
	return SetupQuad(quadOut, pImagePiece, pos.x, pos.y, pImagePiece->width, pImagePiece->height);
}

bool Renderer2D_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y)
{
	return SetupQuad(quadOut, pImagePiece, x, y, pImagePiece->width, pImagePiece->height);
}

bool Renderer2D_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos, const Vector2& size)
{
	return SetupQuad(quadOut, pImagePiece, pos.x, pos.y, size.x, size.y);
}

bool Renderer2D_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y, float width, float height)
{
	float fHalfWidth = width*0.5f;
	float fHalfHeight = height*0.5f;

	quadOut.verts[0].x = -fHalfWidth;
	quadOut.verts[0].y = -fHalfHeight;
	quadOut.verts[0].z = 0.0f;
	quadOut.verts[0].u = pImagePiece->u;
	quadOut.verts[0].v = pImagePiece->v;

	quadOut.verts[1].x = -fHalfWidth;
	quadOut.verts[1].y = fHalfHeight;
	quadOut.verts[1].z = 0.0f;
	quadOut.verts[1].u = pImagePiece->u;
	quadOut.verts[1].v = pImagePiece->v + pImagePiece->dv;

	quadOut.verts[2].x = fHalfWidth;
	quadOut.verts[2].y = -fHalfHeight;
	quadOut.verts[2].z = 0.0f;
	quadOut.verts[2].u = pImagePiece->u + pImagePiece->du;
	quadOut.verts[2].v = pImagePiece->v;

	quadOut.verts[3].x = fHalfWidth;
	quadOut.verts[3].y = fHalfHeight;
	quadOut.verts[3].z = 0.0f;
	quadOut.verts[3].u = pImagePiece->u + pImagePiece->du;
	quadOut.verts[3].v = pImagePiece->v + pImagePiece->dv;

	return true;
}

void Renderer2D_Impl::UpdateFinalMatrix()
{
	m_matModelViewProj = m_matProj * m_matModelView;
	m_matModelViewProjTranspose = m_matModelViewProj;
	m_matModelViewProjTranspose.Transport();
	m_bNeedUpdateFinalMatrix = false;
}
