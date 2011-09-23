/*!
 * \file ActionTestCase.h
 * \date 27-08-2011 04:51:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ACTIONTESTCASE_H__
#define __ACTIONTESTCASE_H__

#include "TestCase.h"
#include <Sprite.h>

class ActionTestCase : public TestCase
{
public:
	DECLARE_RTTI(ActionTestCase, TestCase);

	ActionTestCase();
	virtual ~ActionTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

private:
	Sprite* m_pSprite;
	INode* m_pActionNode;

};
#endif // __ACTIONTESTCASE_H__
