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
	DECLARE_RTTI(Tile, IRenderableObject);

	Tile(const IMAGE_PIECE* pImagePiece, const Vector3& Pos = IMath::VEC3_ZERO);
	~Tile();

	virtual void Render();
	virtual void Update(float dt);
	void SetPosition(const Vector3& pos);
	void SetVisual(bool bVisual);
private:
	bool InitShader();
	INode* GetParentNode();
private:
	const IMAGE_PIECE* m_pImagePiece;
	Vector3 m_vPos;
	IShader* m_pShader;
	bool m_bVisual;
};

#endif // __TILE_H__