/*!
 * \file RendererUI_Impl.cpp
 * \date 8-23-2011 17:33:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RendererUI_Impl.h"
#include <IShaderMgr.h>
#include <util/StringUtil.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <IRenderer2D.h>
#include <msg/MsgCommon.h>
#include <msg/MsgID.h>

IRendererUI& IRendererUI::GetInstance()
{
	static RendererUI_Impl s_RendererUI_Impl;
	return s_RendererUI_Impl;
}

RendererUI_Impl::RendererUI_Impl()
{
	StringUtil::ZeroMemory(m_pCaches_POS_UV, sizeof(m_pCaches_POS_UV));
	m_pShader_POS_UV = NULL;

	m_pTexture = NULL;
	m_bRenderBegan = false;
}

RendererUI_Impl::~RendererUI_Impl()
{
	// TODO: 
}

bool RendererUI_Impl::Initialize()
{
	m_pShader_POS_UV = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if (!m_pShader_POS_UV) return false;

	for (int i = 0; i < NUM_POS_UV_CACHE; ++i)
	{
		int nVertexAttributeSize = m_pShader_POS_UV->GetVertexAttribute()->GetStride();
		m_pCaches_POS_UV[i] = new VertexCache(4*NUM_POS_UV_PRIMETIVE_PER_CACHE*nVertexAttributeSize, 6*NUM_POS_UV_PRIMETIVE_PER_CACHE);
		if (!m_pCaches_POS_UV[i] || !m_pCaches_POS_UV[i]->IsOK()) return false;
		m_pCaches_POS_UV[i]->ConnectEvent(MI_RENDERER_UI_FLUSH, this, (MSG_CALLBACK)&RendererUI_Impl::OnTriangleCacheFlushed);
	}

	return true;
}

void RendererUI_Impl::Terminate()
{
	for (int i = 0; i < NUM_POS_UV_CACHE; ++i)
	{
		SAFE_DELETE(m_pCaches_POS_UV[i]);
	}
	SAFE_RELEASE(m_pShader_POS_UV);
}

void RendererUI_Impl::SetTexture(ITexture* pTexture)
{
	m_pTexture = pTexture;
}

void RendererUI_Impl::DrawTriangleList(const VATTR_POS_UV* pVerts, uint nVerts, const ushort* pIndis, uint nIndis)
{
	AddPrimetive(m_pCaches_POS_UV, NUM_POS_UV_CACHE, m_pShader_POS_UV, m_pTexture, pVerts, nVerts, pIndis, nIndis);
}

void RendererUI_Impl::DrawRect(const QUAD_VERT_POS_UV& quad)
{
	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};
	AddPrimetive(m_pCaches_POS_UV, NUM_POS_UV_CACHE, m_pShader_POS_UV, m_pTexture, &quad.verts[0], 4, s_Indis, 6);
}

void RendererUI_Impl::DrawRect(const Vector2& pos, const IMAGE_PIECE* pImagePiece)
{
	DrawRect(pos.x, pos.y, pImagePiece->width, pImagePiece->height, pImagePiece);
}

void RendererUI_Impl::DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece)
{
	DrawRect(x, y, pImagePiece->width, pImagePiece->height, pImagePiece);
}

void RendererUI_Impl::DrawRect(const Vector2& pos, const Vector2& size, const IMAGE_PIECE* pImagePiece)
{
	DrawRect(pos.x, pos.y, size.x, size.y, pImagePiece);
}

void RendererUI_Impl::DrawRect(float x, float y, float width, float height, const IMAGE_PIECE* pImagePiece)
{
	static VATTR_POS_UV s_Verts[4] =
	{
		{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f},
		{-0.5f, +0.5f, 0.0f, 0.0f, 1.0f},
		{+0.5f, -0.5f, 0.0f, 1.0f, 0.0f},
		{+0.5f, +0.5f, 0.0f, 1.0f, 1.0f},
	};

	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};

	s_Verts[0].x = x;
	s_Verts[0].y = y + height;
	s_Verts[0].u = pImagePiece->u;
	s_Verts[0].v = pImagePiece->v;

	s_Verts[1].x = x;
	s_Verts[1].y = y;
	s_Verts[1].u = pImagePiece->u;
	s_Verts[1].v = pImagePiece->v + pImagePiece->dv;

	s_Verts[2].x = x + width;
	s_Verts[2].y = y + height;
	s_Verts[2].u = pImagePiece->u + pImagePiece->du;
	s_Verts[2].v = pImagePiece->v;

	s_Verts[3].x = x + width;
	s_Verts[3].y = y;
	s_Verts[3].u = pImagePiece->u + pImagePiece->du;
	s_Verts[3].v = pImagePiece->v + pImagePiece->dv;

	AddPrimetive(m_pCaches_POS_UV, NUM_POS_UV_CACHE, m_pShader_POS_UV, pImagePiece->pTexture, &s_Verts[0], 4, s_Indis, 6);
}

void RendererUI_Impl::DrawRect(const Vector2& pos, const Vector2& size, const IMAGE_FRAME* pImageFrame)
{
	DrawRect(pos.x, pos.y, size.x, size.y, pImageFrame);
}

void RendererUI_Impl::DrawRect(float x, float y, float width, float height, const IMAGE_FRAME* pImageFrame)
{
	// top left
 	DrawRect(x, y, pImageFrame->pImagePiece[IFB_TOP_LEFT]);

	// top center
	DrawRect(x + pImageFrame->pImagePiece[IFB_TOP_LEFT]->width, y,
		width - pImageFrame->pImagePiece[IFB_TOP_LEFT]->width - pImageFrame->pImagePiece[IFB_TOP_RIGHT]->width,
		pImageFrame->pImagePiece[IFB_TOP_CENTER]->height,
		pImageFrame->pImagePiece[IFB_TOP_CENTER]);

	// top right
	DrawRect(x + width - pImageFrame->pImagePiece[IFB_TOP_RIGHT]->width, y, pImageFrame->pImagePiece[IFB_TOP_RIGHT]);

	// middle left
	DrawRect(x, y + pImageFrame->pImagePiece[IFB_TOP_LEFT]->height,
		pImageFrame->pImagePiece[IFB_MIDDLE_LEFT]->width,
		height - pImageFrame->pImagePiece[IFB_TOP_LEFT]->height - pImageFrame->pImagePiece[IFB_BOTTOM_LEFT]->height,
		pImageFrame->pImagePiece[IFB_MIDDLE_LEFT]);

	// middle center
	DrawRect(x + pImageFrame->pImagePiece[IFB_MIDDLE_LEFT]->width, y + pImageFrame->pImagePiece[IFB_TOP_CENTER]->height,
		width - pImageFrame->pImagePiece[IFB_MIDDLE_LEFT]->width - pImageFrame->pImagePiece[IFB_MIDDLE_RIGHT]->width,
		height - pImageFrame->pImagePiece[IFB_TOP_CENTER]->height - pImageFrame->pImagePiece[IFB_BOTTOM_CENTER]->height,
		pImageFrame->pImagePiece[IFB_MIDDLE_CENTER]);

	// middle right
	DrawRect(x + width - pImageFrame->pImagePiece[IFB_MIDDLE_RIGHT]->width,
		y + pImageFrame->pImagePiece[IFB_TOP_RIGHT]->height,
		pImageFrame->pImagePiece[IFB_MIDDLE_RIGHT]->width,
		height - pImageFrame->pImagePiece[IFB_TOP_RIGHT]->height - pImageFrame->pImagePiece[IFB_TOP_RIGHT]->height,
		pImageFrame->pImagePiece[IFB_MIDDLE_RIGHT]);

	// bottom left
	DrawRect(x, y + height - pImageFrame->pImagePiece[IFB_BOTTOM_LEFT]->height, pImageFrame->pImagePiece[IFB_BOTTOM_LEFT]);

	// bottom center
	DrawRect(x + pImageFrame->pImagePiece[IFB_BOTTOM_LEFT]->width,
		y + height - pImageFrame->pImagePiece[IFB_BOTTOM_CENTER]->height,
		width - pImageFrame->pImagePiece[IFB_BOTTOM_LEFT]->width - pImageFrame->pImagePiece[IFB_BOTTOM_RIGHT]->width,
		pImageFrame->pImagePiece[IFB_BOTTOM_CENTER]->height,
		pImageFrame->pImagePiece[IFB_BOTTOM_CENTER]);

	// bottom right
	DrawRect(x + width - pImageFrame->pImagePiece[IFB_BOTTOM_RIGHT]->width,
		y + height - pImageFrame->pImagePiece[IFB_BOTTOM_RIGHT]->height,
		pImageFrame->pImagePiece[IFB_BOTTOM_RIGHT]);
}

Vector2 RendererUI_Impl::CalculateSizeWithFrame(const Vector2& size, const IMAGE_FRAME* pImageFrame)
{
	// TODO: 
	return IMath::VEC2_ZERO;
}

Vector2 RendererUI_Impl::CalculateSizeWithFrame(float width, float height, const IMAGE_FRAME* pImageFrame)
{
	// TODO: 
	return IMath::VEC2_ZERO;
}

bool RendererUI_Impl::ClipRect(QUAD_VERT_POS_UV& quadInOut, const Vector2& pos, const Vector2& size)
{
	return ClipRect(quadInOut, pos.x, pos.y, size.x, size.y);
}

bool RendererUI_Impl::ClipRect(QUAD_VERT_POS_UV& quadInOut, float x, float y, float width, float height)
{
	//determine whether rect in the Quad
	if((quadInOut.verts[0].x > x + width)
		||(quadInOut.verts[3].x < x)
		||(quadInOut.verts[0].y < y)
		||(quadInOut.verts[3].y > y + height))
		return false;

	if( quadInOut.verts[0].x < x)
	{
		float fAlpha = (x - quadInOut.verts[0].x) / (quadInOut.verts[2].x - quadInOut.verts[0].x);
		float u = quadInOut.verts[0].u * (1.0f - fAlpha) + quadInOut.verts[2].u * fAlpha;
		quadInOut.verts[0].x = x;
		quadInOut.verts[0].u = u;
		quadInOut.verts[1].x = x;
		quadInOut.verts[1].u = u;
	}
	
	if(quadInOut.verts[2].x > x + width)
	{
		float fAlpha = ((x + width) - quadInOut.verts[0].x) / (quadInOut.verts[3].x - quadInOut.verts[0].x);
		float u = quadInOut.verts[0].u * (1.0f - fAlpha) + quadInOut.verts[2].u * fAlpha;

		quadInOut.verts[2].x = x +width;
		quadInOut.verts[2].u = u;
		quadInOut.verts[3].x = x +width;
		quadInOut.verts[3].u = u;
	}

	if(quadInOut.verts[1].y < y)
	{
		float fAlpha =(y - quadInOut.verts[1].y) / (quadInOut.verts[0].y - quadInOut.verts[1].y);
		float v = quadInOut.verts[0].v *  fAlpha + quadInOut.verts[1].v * (1.0f - fAlpha);

		quadInOut.verts[1].y = y;
		quadInOut.verts[1].v = v;
		quadInOut.verts[3].y = y;
		quadInOut.verts[3].v = v;
	}

	if( quadInOut.verts[0].y > y + height)
	{
		float fAlpha = ((y + height) - quadInOut.verts[1].y) / (quadInOut.verts[0].y - quadInOut.verts[1].y);
		float v = quadInOut.verts[0].v *  fAlpha + quadInOut.verts[1].v * (1.0f - fAlpha);

		quadInOut.verts[0].y = y + height;
		quadInOut.verts[0].v = v;
		quadInOut.verts[2].y = y + height;
		quadInOut.verts[2].v = v;
	}

	return true;
}

bool RendererUI_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos)
{
	return SetupQuad(quadOut, pImagePiece, pos.x, pos.y, pImagePiece->width, pImagePiece->height);
}

bool RendererUI_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y)
{
	return SetupQuad(quadOut, pImagePiece, x, y, pImagePiece->width, pImagePiece->height);
}

bool RendererUI_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos, const Vector2& size)
{
	return SetupQuad(quadOut, pImagePiece, pos.x, pos.y, size.x, size.y);
}

bool RendererUI_Impl::SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y, float width, float height)
{
	if (width <= 0.0f || height <= 0.0f) return false;

	quadOut.verts[0].x = x;
	quadOut.verts[0].y = y + height;
	quadOut.verts[0].z = 0.0f;
	quadOut.verts[0].u = pImagePiece->u;
	quadOut.verts[0].v = pImagePiece->v;

	quadOut.verts[1].x = x;
	quadOut.verts[1].y = y;
	quadOut.verts[1].z = 0.0f;
	quadOut.verts[1].u = pImagePiece->u;
	quadOut.verts[1].v = pImagePiece->v + pImagePiece->dv;

	quadOut.verts[2].x = x + width;
	quadOut.verts[2].y = y + height;
	quadOut.verts[2].z = 0.0f;
	quadOut.verts[2].u = pImagePiece->u + pImagePiece->du;
	quadOut.verts[2].v = pImagePiece->v;

	quadOut.verts[3].x = x + width;
	quadOut.verts[3].y = y;
	quadOut.verts[3].z = 0.0f;
	quadOut.verts[3].u = pImagePiece->u + pImagePiece->du;
	quadOut.verts[3].v = pImagePiece->v + pImagePiece->dv;

	return true;
}

void RendererUI_Impl::BeginRender()
{
	if (m_bRenderBegan) return;

	m_bRenderBegan = true;
	m_pTexture = NULL;

	// set transform matrix for ui
	const Vector2& halfScreenSize = ScreenUtil::GetInstance().GetHalfScreenSize();
	Matrix4x4 matModelView;
	IMath::BuildTranslateMatrix(matModelView, -halfScreenSize.x, halfScreenSize.y, 0.0f);
	matModelView.e[Matrix4x4::E22] = -1.0f;
	IRenderer2D::GetInstance().SetModelViewMatrix(matModelView);
}

void RendererUI_Impl::EndRender()
{
	if (!m_bRenderBegan) return;

	for (int i = 0; i < NUM_POS_UV_CACHE; ++i)
	{
		m_pCaches_POS_UV[i]->Flush();
		m_pCaches_POS_UV[i]->SetShader(NULL);
		m_pCaches_POS_UV[i]->SetTexture(NULL);
	}

	m_pShader_POS_UV->Reset();

	m_pTexture = NULL;
	m_bRenderBegan = false;
}

bool RendererUI_Impl::AddPrimetive(VertexCache** pCache, int nNumCache, IShader* pShader, ITexture* pTexture, const void* pVerts, uint nVerts, const ushort* pIndis, uint nIndis)
{
	if (!m_bRenderBegan) return false;

	VertexCache* pEmptyCache = NULL;
	VertexCache* pMatchCache = NULL;

	for (int i = 0; i < nNumCache; ++i)
	{
		if (pCache[i]->GetShader() == pShader
			&& pCache[i]->GetTexture() == pTexture)
		{
			pMatchCache = pCache[i];
			break;
		}

		if (!pEmptyCache && pCache[i]->GetNumVerts() == 0)
		{
			pEmptyCache = pCache[i];
		}
	}

	if (pMatchCache)
	{
		if (!pMatchCache->AddVerts(pVerts, nVerts, pIndis, nIndis))
		{
			pMatchCache->Flush();
			bool bOK = pMatchCache->AddVerts(pVerts, nVerts, pIndis, nIndis);
			if (!bOK)
			{
				LOGE("IRendererUI AddPrimetive Failed with nVerts:%d, nIndis:%d", nVerts, nIndis);
				return false;
			}
		}
	}
	else if (pEmptyCache)
	{
		pEmptyCache->SetTexture(pTexture);
		pEmptyCache->SetShader(pShader);
		bool bOK = pEmptyCache->AddVerts(pVerts, nVerts, pIndis, nIndis);
		if (!bOK)
		{
			LOGE("IRendererUI AddPrimetive Failed with nVerts:%d, nIndis:%d", nVerts, nIndis);
			return false;
		}
	}
	else
	{
		LOGE("IRendererUI no more valid vertex cache");
		return false;
	}

	return true;
}

bool RendererUI_Impl::OnTriangleCacheFlushed(IMsgBase* pMsg)
{
	MsgCommon* pMsgFlush = (MsgCommon*)pMsg;

	VertexCache* pCache = (VertexCache*)pMsgFlush->GetObject();
	if (!pCache) return false;

	ITexture* pTexture = pCache->GetTexture();
	IShader* pShader = pCache->GetShader();

	if (pTexture) pShader->SetTexture("u_texture", pTexture);
	pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	IRenderer2D::GetInstance().DrawTriangleList(pCache->GetVerts(), pCache->GetNumVerts(), pCache->GetIndis(), pCache->GetNumIndis(), pShader);
	return true;
}
