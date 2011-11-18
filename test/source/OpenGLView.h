/*!
 * \file OpenGLView.h
 * \date 11-08-2011 11:21:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __OPENGLVIEW_H__
#define __OPENGLVIEW_H__

#include <IViewOpenGL.h>
#include "TestCase.h"
#include <ui/UIString.h>
#include <vector>

class OpenGLView : public IViewOpenGL
{
public:
	typedef std::vector<TestCase*> TV_TEST_CASE;

public:
	DECLARE_RTTI(OpenGLView, IViewOpenGL);

	OpenGLView();
	virtual ~OpenGLView();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	bool OnMsgTouch(IMsgBase* pMsg);
	bool OnBtnTestCaseClicked(IMsgBase* pMsg);
	bool OnBtnReturnClicked(IMsgBase* pMsg);

	bool AddTestCase(TestCase* pTestCase, UIScreen* pScreen);
	void RemoveCurrTestCase();
	bool SwitchTestCase(int nIndex);

	bool InitializeTestCase();
	void TerminateTestCase();

private:
	TV_TEST_CASE m_vTestCase;
	TestCase* m_pCurrTestCase;
	UIScreen* m_pMainScreen;
	UIString* m_pFPS;
	int m_nFPS;
	float m_fFPSTime;
	Vector2 m_vTextViewPos;
	int m_nIndex;

};
#endif // __OPENGLVIEW_H__
