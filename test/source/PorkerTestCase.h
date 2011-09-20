/*!
 * \file PorkerTestCase
 * \date 2011/9/20 20:42
 *
 *
 * \author wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __PORKERTESTCASE_H_
#define __PORKERTESTCASE_H_
#include "TestCase.h"
#include <ITexture.h>
#include <IShader.h>
class PorkerTestCase : public TestCase
{
public:
	DECLARE_RTTI(PorkerTestCase, TestCase);

	PorkerTestCase();
	virtual ~PorkerTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();
	virtual void Render();
private:
	ITexture* m_pBackGroundTexture;
	IShader* m_pShader;	
};
#endif//__PORKERTESTCASE_H_