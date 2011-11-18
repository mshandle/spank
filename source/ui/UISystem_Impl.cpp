/*!
 * \file UISystem_Impl.cpp
 * \date 8-24-2011 14:50:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UISystem_Impl.h"
#include <ui/IRendererUI.h>
#include <util/ScreenUtil.h>

IUISystem& IUISystem::GetInstance()
{
	static UISystem_Impl s_UISystem_Impl;
	return s_UISystem_Impl;
}

UISystem_Impl::UISystem_Impl()
{
	m_pCurrScreen = NULL;
	m_pWinMouseCapture = NULL;
}

UISystem_Impl::~UISystem_Impl()
{
	// TODO: 
}

bool UISystem_Impl::Initialize()
{
	m_pCurrScreen = CreateUIScreen();
	return true;
}

void UISystem_Impl::Terminate()
{
	for (TV_UISCREEN::iterator it = m_vUIScreen.begin(); it != m_vUIScreen.end(); ++it)
	{
		UIScreen* pScreen = (*it);
		SAFE_DELETE(pScreen);
	}
	m_vUIScreen.clear();
	m_pCurrScreen = NULL;
}

void UISystem_Impl::Update(float dt)
{
	if (!m_pCurrScreen) return;

	m_pCurrScreen->Update(dt);
}

void UISystem_Impl::Render()
{
	if (!m_pCurrScreen) return;

	UIRect rect(IMath::VEC2_ZERO, ScreenUtil::GetInstance().GetScreenSize());
	RenderParam param(IMath::VEC2_ZERO, rect);
	m_pCurrScreen->Render(param);
}

UIScreen* UISystem_Impl::GetCurrentScreen()
{
	return m_pCurrScreen;
}

bool UISystem_Impl::SetCurrentScreen(UIScreen* pUIScreen)
{
	if (!FindUIScreen(pUIScreen)) return false;
	if (m_pCurrScreen == pUIScreen) return false;

	m_pCurrScreen = pUIScreen;
	ReleaseMouse();
	return true;
}

UIScreen* UISystem_Impl::CreateUIScreen()
{
	UIScreen* pScreen = new UIScreen();
	if (!pScreen || !pScreen->IsOK())
	{
		SAFE_DELETE(pScreen);
		return NULL;
	}

	pScreen->SetPosition(IMath::VEC2_ZERO);
	pScreen->SetSize(ScreenUtil::GetInstance().GetScreenSize());
	m_vUIScreen.push_back(pScreen);

	return pScreen;
}

bool UISystem_Impl::ReleaseUIScreen(UIScreen* pUIScreen)
{
	for (TV_UISCREEN::iterator it = m_vUIScreen.begin(); it != m_vUIScreen.end(); ++it)
	{
		UIScreen* pScreen = (*it);
		if (pScreen == pUIScreen)
		{
			SAFE_DELETE(pScreen);
			m_vUIScreen.erase(it);
			if (m_pCurrScreen == pUIScreen)
			{
				m_pCurrScreen = NULL;
				ReleaseMouse();
			}
			return true;
		}
	}

	return false;
}

bool UISystem_Impl::CaptureMouse(UIWindow* pWindow)
{
	if (m_pWinMouseCapture != NULL || pWindow == NULL) return false;
	m_pWinMouseCapture = pWindow;
	return true;
}

bool UISystem_Impl::ReleaseMouse()
{
	if (m_pWinMouseCapture == NULL) return false;
	m_pWinMouseCapture = NULL;
	return true;
}

bool UISystem_Impl::ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType)
{
	if (!m_pCurrScreen) return false;

	if (m_pWinMouseCapture)
	{
		Vector2 posRelative = pos - m_pWinMouseCapture->GetPositionAbsolute();
		return m_pWinMouseCapture->ProcessTouchEvent(posRelative, eType);
	}

	return m_pCurrScreen->ProcessTouchEvent(pos, eType);
}

bool UISystem_Impl::FindUIScreen(UIScreen* pUIScreen)
{
	for (TV_UISCREEN::iterator it = m_vUIScreen.begin(); it != m_vUIScreen.end(); ++it)
	{
		UIScreen* pScreen = (*it);
		if (pScreen == pUIScreen) return true;
	}

	return false;
}
