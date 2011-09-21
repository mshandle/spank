/*!
 * \file RendererUI_Impl.h
 * \date 8-23-2011 17:32:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERERUI_IMPL_H__
#define __RENDERERUI_IMPL_H__

#include <ui/IRendererUI.h>
#include "VertexCache.h"
#include <IShader.h>

class RendererUI_Impl : public IRendererUI
{
public:
	enum CONST_DEFINE
	{
// 		NUM_POS_RGB_CACHE = 1,
// 		NUM_POS_RGB_PRIMETIVE_PER_CACHE = 128,

		NUM_POS_UV_CACHE = 10,
		NUM_POS_UV_PRIMETIVE_PER_CACHE = 128,
	};

public:
	DECLARE_RTTI(RendererUI_Impl, IRendererUI);

	RendererUI_Impl();
	virtual ~RendererUI_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void SetTexture(ITexture* pTexture);

// 	virtual void DrawLineList(const VATTR_POS_RGB* pVerts, uint nVerts, const ushort* pIndis, uint nIndis);
// 	virtual void DrawLineRect(const QUAD_VERT_POS_RGB& quad);
// 	virtual void DrawLineRect(const Vector2& pos, const Vector2& size);
// 	virtual void DrawLineRect(float x, float y, float width, float height);
// 	virtual void SetColor(float r, float g, float b, float a);

	virtual void DrawTriangleList(const VATTR_POS_UV* pVerts, uint nVerts, const ushort* pIndis, uint nIndis);

	virtual void DrawRect(const QUAD_VERT_POS_UV& quad);

	virtual void DrawRect(const Vector2& pos, const IMAGE_PIECE* pImagePiece);
	virtual void DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece);
	virtual void DrawRect(const Vector2& pos, const Vector2& size, const IMAGE_PIECE* pImagePiece);
	virtual void DrawRect(float x, float y, float width, float height, const IMAGE_PIECE* pImagePiece);

	virtual void DrawRect(const Vector2& pos, const Vector2& size, const IMAGE_FRAME* pImageFrame);
	virtual void DrawRect(float x, float y, float width, float height, const IMAGE_FRAME* pImageFrame);

	virtual Vector2 CalculateSizeWithFrame(const Vector2& size, const IMAGE_FRAME* pImageFrame);
	virtual Vector2 CalculateSizeWithFrame(float width, float height, const IMAGE_FRAME* pImageFrame);

	virtual bool ClipRect(QUAD_VERT_POS_UV& quadInOut, const Vector2& pos, const Vector2& size);
	virtual bool ClipRect(QUAD_VERT_POS_UV& quadInOut, float x, float y, float width, float height);

	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos);
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y);
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos, const Vector2& size);
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y, float width, float height);

	virtual void BeginRender();
	virtual void EndRender();

private:
	bool AddPrimetive(VertexCache** pCache, int nNumCache, IShader* pShader, ITexture* pTexture, const void* pVerts, uint nVerts, const ushort* pIndis, uint nIndis);
// 	bool OnLineCacheFlushed(IMsgBase* pMsg);
	bool OnTriangleCacheFlushed(IMsgBase* pMsg);

private:
// 	VertexCache* m_pCaches_POS_RGB[NUM_POS_RGB_CACHE];
// 	IShader* m_pShader_POS_RGB;

	VertexCache* m_pCaches_POS_UV[NUM_POS_UV_CACHE];
	IShader* m_pShader_POS_UV;

	ITexture* m_pTexture;
// 	Vector4 m_vColor;
	bool m_bRenderBegan;

};
#endif // __RENDERERUI_IMPL_H__
