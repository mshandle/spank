/*!
 * \file Tile.h
 * \date 2011/09/21 18:06
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __TILE_H__
#define __TILE_H__

#include "IRenderableObject.h"
#include "BaseTypeEx.h"
#include "INode.h"
#include "IShader.h"

class Tile :public IRenderableObject
{
public:
	enum RENDER_TYPE
	{
		NORMAL = 0,
		GRAY,
	};
	const static char* pszShaderFileName[];
	DECLARE_RTTI(Tile, IRenderableObject);

	Tile(const IMAGE_PIECE* pImagePiece);
	virtual ~Tile();

	virtual void Render();
	virtual void Update(float dt);

	void SetRenderType(RENDER_TYPE eType);
	void SetSize(float width, float height);
	void SetVisible(bool bVisible);
	bool IsVisible() const;

private:
	bool InitShader();
	INode* GetParentNode();

private:
	const IMAGE_PIECE* m_pImagePiece;
	IShader* m_pShader;
	bool m_bVisible;
	float m_nWidth;
	float m_nHeight;
	RENDER_TYPE m_eType;
};

#endif // __TILE_H__
