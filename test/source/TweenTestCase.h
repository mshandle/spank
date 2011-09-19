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
#include <vector>
#include <string>
class TweenTestCase : public TestCase
{
public:
	typedef std::vector<IActionBase*> TV_ACTIONLOOP;
public:
	DECLARE_RTTI(TweenTestCase, TestCase);

	TweenTestCase();
	virtual ~TweenTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();
	virtual void Render();
private:
	void OnPrvButton(IMsgBase* pMsg);
	void OnNextButton(IMsgBase* pMsg);
	void OnEASEInButton(IMsgBase* pMsg);
	void OnEASEOutButton(IMsgBase* pMsg);
	void OnEASEInOutButton(IMsgBase* pMsg);

	void UpdateTween();
private:
	Sprite* m_pSpriteAction;
	ActionSequeue* m_pActionSequeue;
	ActionLoop* m_pActionLoop;
	INode* m_pActionNode;
	uint m_nIndexTween;
	uint m_nEffectIndex;
	TV_ACTIONLOOP m_vActionLoop;
	const static int TWEEN_TYPE_SIZE = 3;

	
	
};
#endif // __TWEENTESTCASE_H__
