/*!
 * \file ClipRectTestCase.h
 * \date 2011/09/15 15:22
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __CLIPRECTESTCASE_H__
#define __CLIPRECTESTCASE_H__

#include "TestCase.h"

class ClipRectTestCase :public TestCase
{
public:
	DECLARE_RTTI(ClipRectTestCase, TestCase);

	ClipRectTestCase();
	virtual ~ClipRectTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	const IMAGE_PIECE* m_pStyle[DUS_BUTTON_NUM];

};
#endif // __CLIPRECTESTCASE_H__
