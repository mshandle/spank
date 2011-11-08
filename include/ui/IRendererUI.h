/*!
 * \file IRendererUI.h
 * \date 8-23-2011 16:02:44
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRENDERERUI_H__
#define __IRENDERERUI_H__

#include "../ISingleton.h"
#include "BaseTypeUI.h"

class IRendererUI : public ISingleton
{
public:
	DECLARE_RTTI(IRendererUI, ISingleton);

	static IRendererUI& GetInstance();

	virtual void SetTexture(ITexture* pTexture) = 0;

	virtual void DrawTriangleList(const VATTR_POS_UV* pVerts, uint nVerts, const ushort* pIndis, uint nIndis) = 0;
	virtual void DrawRect(const QUAD_VERT_POS_UV& quad) = 0;
	virtual void DrawRect(const Vector2& pos, const IMAGE_PIECE* pImagePiece) = 0;
	virtual void DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece) = 0;
	virtual void DrawRect(const Vector2& pos, const Vector2& size, const IMAGE_PIECE* pImagePiece) = 0;
	virtual void DrawRect(float x, float y, float width, float height, const IMAGE_PIECE* pImagePiece) = 0;
	virtual void DrawRect(const Vector2& pos, const Vector2& size, const IMAGE_FRAME* pImageFrame) = 0;
	virtual void DrawRect(float x, float y, float width, float height, const IMAGE_FRAME* pImageFrame) = 0;

	virtual Vector2 CalculateSizeWithFrame(const Vector2& size, const IMAGE_FRAME* pImageFrame) = 0;
	virtual Vector2 CalculateSizeWithFrame(float width, float height, const IMAGE_FRAME* pImageFrame) = 0;

	virtual bool ClipRect(QUAD_VERT_POS_UV& quadInOut, const Vector2& pos, const Vector2& size) = 0;
	virtual bool ClipRect(QUAD_VERT_POS_UV& quadInOut, float x, float y, float width, float height) = 0;

	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos) = 0;
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y) = 0;
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, const Vector2& pos, const Vector2& size) = 0;
	virtual bool SetupQuad(QUAD_VERT_POS_UV& quadOut, const IMAGE_PIECE* pImagePiece, float x, float y, float width, float height) = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;

};
#endif // __IRENDERERUI_H__
