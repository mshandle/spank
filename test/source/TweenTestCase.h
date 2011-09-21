/*!
 * \file TweenTestCase.h
 * \date 2011/09/16 14:34
 *	
 *	
 * \author:	wbaoqing(wbaoqin@gmail.com)
 */
#ifndef __TWEENTESTCASE_H__
#define __TWEENTESTCASE_H__

#include "TestCase.h"
#include <Sprite.h>
#include <action/ActionSequeue.h>
#include <action/ActionLoop.h>
#include <ui/UITextView.h>
#include <vector>

class TweenTestCase : public TestCase
{
public:
	enum CONST_DEFINE
	{
		TWEEN_TYPE_SIZE = 3,
	};

	typedef std::vector<IActionBase*> TV_ACTIONLOOP;

public:
	DECLARE_RTTI(TweenTestCase, TestCase);

	TweenTestCase();
	virtual ~TweenTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();
	virtual void Render();

	bool OnPrvButton(IMsgBase* pMsg);
	bool OnNextButton(IMsgBase* pMsg);
	bool OnEASEInButton(IMsgBase* pMsg);
	bool OnEASEOutButton(IMsgBase* pMsg);
	bool OnEASEInOutButton(IMsgBase* pMsg);

private:
	void UpdateTween();

private:
	IShader* m_pShader;
	Sprite* m_pSpriteAction;
	INode* m_pActionNode;
	uint m_nIndexTween;
	uint m_nEffectIndex;
	UITextView* m_pUiText;
	TV_ACTIONLOOP m_vActionLoop;
	const IMAGE_PIECE* m_pImagePiece;

};
#endif // __TWEENTESTCASE_H__
