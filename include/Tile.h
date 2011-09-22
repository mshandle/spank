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
class Tile :public IRenderableObject
{
public:
	DECLARE_RTTI(Tile, IRenderableObject);

	Tile(const IMAGE_PIECE* pImagePiece);
	~Tile();

	virtual void Render();
	virtual void Update(float dt);
private:
	bool InitShader();
	INode* GetParentNode();
private:
	const IMAGE_PIECE* m_pImagePiece;

};

#endif // __TILE_H__