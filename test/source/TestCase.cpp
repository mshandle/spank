/*!
 * \file TestCase.cpp
 * \date 8-25-2011 9:29:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "TestCase.h"
#include <ui/IUISystem.h>
#include <ui/UITextView.h>
#include <util/ScreenUtil.h>
#include <msg/MsgCommon.h>
#include <ui/uimsg/UIMsgID.h>
#include "UserMsgID.h"

TestCase::TestCase(const char* pszTestName)
{
	if (pszTestName)
	{
		m_strTestName = pszTestName;
	}
	else
	{
		m_strTestName = "Unknown";
	}

	m_pUIScreen = NULL;
	m_bOK = true;
}

TestCase::~TestCase()
{
	// TODO: 
}

const char* TestCase::GetName() const
{
	return m_strTestName.c_str();
}

UIScreen* TestCase::GetScreen()
{
	return m_pUIScreen;
}

bool TestCase::InternalInitialize()
{
	m_pUIScreen = IUISystem::GetInstance().CreateUIScreen();
	if (!m_pUIScreen) return false;

	if (!Initialize(m_pUIScreen)) return false;
	AddReturnButton(m_pUIScreen);

	return true;
}

void TestCase::InternalTerminate()
{
	Terminate();

	IUISystem::GetInstance().ReleaseUIScreen(m_pUIScreen);
	m_pUIScreen = NULL;
}

void TestCase::AddReturnButton(UIScreen* pUIScreen)
{
	UITextView* pTextView = new UITextView(pUIScreen, IMath::VEC2_ZERO, "RETURN");

	Vector2 pos(0.0f, ScreenUtil::GetInstance().GetScreenHeight() - pTextView->GetSize().y);
	pTextView->SetPosition(pos);
	pTextView->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&TestCase::OnBtnReturnClicked);
}

bool TestCase::OnBtnReturnClicked(IMsgBase* pMsg)
{
	// return to menu
	MsgCommon msgCommon(MI_USER_RETURN);
	CallEvent(msgCommon);
	return true;
}
