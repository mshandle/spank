/*!
 * \file GameApp.cpp
 * \date 7-21-2011 14:42:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameApp.h"
#include <util/ScreenUtil.h>
#include <util/IDebugUtil.h>
#include <msg/MsgMgr.h>
#include <msg/MsgTouch.h>

#include <ui/uimsg/MsgClick.h>
#include <ui/uimsg/UIMsgID.h>

#include <ui/IUISystem.h>
#include <ui/UITextView.h>
#include <IResourceMgr.h>
#include "UserMsgID.h"
#include "UITestCase.h"
#include "SpriteTestCase.h"
#include "ActionTestCase.h"
#include "ParticleTestCase.h"
#include "MapTestCase.h"
#include "Box2DTestCase.h"
#include "ClipRectTestCase.h"
#include "TweenTestCase.h"
#include "PorkerTestCase.h"
IGameApp& IGameApp::GetInstance()
{
	static GameApp s_GameApp;
	return s_GameApp;
}

GameApp::GameApp()
{
	m_pCurrTestCase = NULL;
	m_pMainScreen = NULL;
	m_vTextViewPos = IMath::VEC2_ZERO;
}

GameApp::~GameApp()
{
	// TODO: 
}

bool GameApp::Initialize()
{
	MsgMgr::GetInstance().SubscribeMessage(MI_TOUCH, this, CAST_MSG_CALLBACK(&GameApp::OnMsgTouch));

	IResourceMgr::GetInstance().AddImagePieceList("test_case.xml");

	m_pMainScreen = IUISystem::GetInstance().GetCurrentScreen();

	// add test case
	AddTestCase(new UITestCase(), m_pMainScreen);
	AddTestCase(new SpriteTestCase(), m_pMainScreen);
	AddTestCase(new ActionTestCase(), m_pMainScreen);
	AddTestCase(new ParticleTestCase(), m_pMainScreen);
	AddTestCase(new MapTestCase(), m_pMainScreen);
	AddTestCase(new Box2DTestCase(), m_pMainScreen);
	AddTestCase(new ClipRectTestCase(), m_pMainScreen);
	AddTestCase(new TweenTestCase(), m_pMainScreen);
	AddTestCase(new PorkerTestCase(), m_pMainScreen);
	return true;
}

void GameApp::Terminate()
{
	FreeCurrTestCase();

	// free test case
	for (TV_TEST_CASE::iterator it = m_vTestCase.begin(); it != m_vTestCase.end(); ++it)
	{
		TestCase* pTestCase = (*it);
		SAFE_DELETE(pTestCase);
	}
}

void GameApp::Update(float dt)
{
	if (m_pCurrTestCase) m_pCurrTestCase->Update(dt);
}

void GameApp::Render()
{
	if (m_pCurrTestCase) m_pCurrTestCase->Render();
}

bool GameApp::OnMsgTouch(IMsgBase* pMsg)
{
	MsgTouch* pMsgTouch = (MsgTouch*)pMsg;

	if (pMsgTouch->IsTouchBegin())
	{
// 		LOGD("touch begin: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_BEGIN);
	}
	else if (pMsgTouch->IsTouchMove())
	{
// 		LOGD("touch move: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_MOVE);
	}
	else if (pMsgTouch->IsTouchEnd())
	{
// 		LOGD("touch end: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_END);
	}

	return true;
}

bool GameApp::OnBtnTestCaseClicked(IMsgBase* pMsg)
{
	MsgClick* pMsgClick = (MsgClick*)pMsg;

	// switch to the new test case
	SwitchTestCase(pMsgClick->GetSenderID());

	return true;
}

bool GameApp::OnBtnReturnClicked(IMsgBase* pMsg)
{
	// free current test case
	FreeCurrTestCase();
	return true;
}

bool GameApp::AddTestCase(TestCase* pTestCase, UIScreen* pScreen)
{
	if (!pTestCase)
	{
		SAFE_RELEASE(pTestCase);
		return false;
	}

	int nIndex = (int)m_vTestCase.size();

	UITextView* pTextView = new UITextView(pScreen, pTestCase->GetName());

	Vector2 pos((ScreenUtil::GetInstance().GetScreenWidth() - pTextView->GetSize().x) / 2.0f, m_vTextViewPos.y);
	pTextView->SetID(nIndex);
	pTextView->SetPosition(pos);
	pTextView->ConnectEvent(UMI_CLICKED, this, CAST_MSG_CALLBACK(&GameApp::OnBtnTestCaseClicked));

	m_vTestCase.push_back(pTestCase);
	pTestCase->ConnectEvent(MI_USER_RETURN, this, CAST_MSG_CALLBACK(&GameApp::OnBtnReturnClicked));

	m_vTextViewPos.y += pTextView->GetSize().y;
	return true;
}

void GameApp::FreeCurrTestCase()
{
	if (m_pCurrTestCase)
	{
		m_pCurrTestCase->InternalTerminate();
		IUISystem::GetInstance().SetCurrentScreen(m_pMainScreen);
		m_pCurrTestCase = NULL;
	}
}

bool GameApp::SwitchTestCase(int nIndex)
{
	if (nIndex < 0 && nIndex >= (int)m_vTestCase.size()) return false;

	TestCase* pTestCase = m_vTestCase[nIndex];
	if (pTestCase != m_pCurrTestCase) FreeCurrTestCase();

	if (!pTestCase->InternalInitialize())
	{
		pTestCase->InternalTerminate();
		LOGE("initialize test case failed %s", pTestCase->GetName());
		return false;
	}

	m_pCurrTestCase = pTestCase;
	IUISystem::GetInstance().SetCurrentScreen(pTestCase->GetScreen());

	return true;
}
