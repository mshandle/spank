/*!
 * \file SpriteTestCase.h
 * \date 27-08-2011 04:52:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SPRITETESTCASE_H__
#define __SPRITETESTCASE_H__

#include "TestCase.h"
#include <Sprite.h>

class SpriteTestCase : public TestCase
{
public:
	DECLARE_RTTI(SpriteTestCase, TestCase);

	SpriteTestCase();
	virtual ~SpriteTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

private:
	bool OnBtnStartClicked(IMsgBase* pMsg);
	bool OnBtnPauseClicked(IMsgBase* pMsg);
	bool OnBtnStopClicked(IMsgBase* pMsg);
	bool OnBtnRestartClicked(IMsgBase* pMsg);

private:
	Sprite* m_pSprite;
	INode* m_pSpriteNode;

};
#endif // __SPRITETESTCASE_H__
