/*!
 * \file Sprite.h
 * \date 30-07-2011 16:18:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "IRenderableObject.h"
#include "BaseTypeEx.h"
#include "IShader.h"
#include "INode.h"

class Sprite : public IRenderableObject
{
public:
	typedef struct SPRITE_FRAME_tag
	{
		const IMAGE_PIECE* pImagePiece;
		float fFrameTime;
	} SPRITE_FRAME;

public:
	DECLARE_RTTI(Sprite, IRenderableObject);

	Sprite(const char* pszSpriteFile);
	virtual ~Sprite();

	virtual void Update(float dt);
	virtual void Render();

	virtual void SetLoop(bool bLoop);

private:
	bool LoadSpriteFromFile(const char* pszSpriteFile);
	INode* GetParentNode();

private:
	IShader* m_pShader;

	int m_nNumFrames;
	SPRITE_FRAME* m_pSpriteFrames;

	float m_fCurrTime;
	int m_nCurrIndex;
	bool m_bLoop;

};
#endif // __SPRITE_H__
