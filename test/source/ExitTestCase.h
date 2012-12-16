/*!
 * \file ExitTestCase.h
 * \date 12-02-2012 16:42:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __EXITTESTCASE_H__
#define __EXITTESTCASE_H__

#include "TestCase.h"

class ExitTestCase : public TestCase
{
public:
	DECLARE_RTTI(ExitTestCase, TestCase);

	ExitTestCase();
	virtual ~ExitTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

};
#endif // __EXITTESTCASE_H__
