/*!
 * \file UIWindow.cpp
 * \date 8-24-2011 15:04:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIWindow.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>

static bool PointInRect(const Vector2& point, const Vector2& rectPos, const Vector2& rectSize)
{
	if (point.x < rectPos.x
		|| point.x > rectPos.x + rectSize.x
		|| point.y < rectPos.y
		|| point.y > rectPos.y + rectSize.y) return false;

	return true;
}

UIWindow::UIWindow(UIWindow* pParent)
{
	m_nID = 0;
	m_vPosition = IMath::VEC2_ZERO;
	m_vSize = IMath::VEC2_ZERO;

	m_MarginLeftTop = IMath::VEC2_ZERO;
	m_MarginRightBottom = IMath::VEC2_ZERO;

	m_pParent = pParent;
	if (m_pParent) m_pParent->AddChild(this);

	m_nState = WS_DEFAULT_STATE;

	m_pLastTouchedWindow = NULL;
}

UIWindow::~UIWindow()
{
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		SAFE_RELEASE(pWindow);
	}
	m_vChildren.clear();
}

UIWindow* UIWindow::GetParentWindow()
{
	return m_pParent;
}

int UIWindow::GetID() const
{
	return m_nID;
}

void UIWindow::SetID(int nID)
{
	m_nID = nID;
}

const Vector2& UIWindow::GetPosition() const
{
	return m_vPosition;
}

void UIWindow::SetPosition(const Vector2& pos)
{
	m_vPosition = pos;
}

const Vector2& UIWindow::GetSize() const
{
	return m_vSize;
}

void UIWindow::SetSize(const Vector2& size)
{
	SetAutoAdjustSize(false);
	m_vSize = size;
}

void UIWindow::SetMargin(float left, float top, float right, float bottom)
{
	m_MarginLeftTop.x = left;
	m_MarginLeftTop.y = top;
	m_MarginRightBottom.x = right;
	m_MarginRightBottom.y = bottom;
}

const Vector2& UIWindow::GetMarginLeftTop() const
{
	return m_MarginLeftTop;
}

const Vector2& UIWindow::GetMarginRightBottom() const
{
	return m_MarginRightBottom;
}

void UIWindow::SetWindowState(uint nMask, bool bSet)
{
	if (bSet)
	{
		m_nState |= nMask;
	}
	else
	{
		m_nState &= (~nMask);
	}
}

bool UIWindow::CheckWindowState(uint nMask) const
{
	return (m_nState & nMask) == nMask;
}

void UIWindow::SetVisible(bool bVisible)
{
	SetWindowState(WS_VISIBLE, bVisible);
}

bool UIWindow::IsVisible() const
{
	return CheckWindowState(WS_VISIBLE);
}

void UIWindow::SetEnable(bool bEnable)
{
	SetWindowState(WS_ENABLE, bEnable);
}

bool UIWindow::IsEnable() const
{
	return CheckWindowState(WS_ENABLE);
}

void UIWindow::SetAutoAdjustSize(bool bAutoAdjustSize)
{
	SetWindowState(WS_AUTO_ADJUST_SIZE, bAutoAdjustSize);
}

bool UIWindow::IsAutoAdjustSize() const
{
	return CheckWindowState(WS_AUTO_ADJUST_SIZE);
}

bool UIWindow::IsPressed() const
{
	return CheckWindowState(WS_PRESSED);
}

void UIWindow::AdjustSize()
{
	if (IsAutoAdjustSize())
	{
		m_vSize = GetBestSize();
	}
}

bool UIWindow::ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType)
{
	UIWindow* pWindow = FindChildUnderPoint(pos);

	if (pWindow)
	{
		if (m_pLastTouchedWindow && m_pLastTouchedWindow != pWindow) m_pLastTouchedWindow->OnTouchLost();
		m_pLastTouchedWindow = pWindow;

		Vector2 localPos = pos - pWindow->GetPosition();
		return pWindow->ProcessTouchEvent(localPos, eType);
	}

	if (m_pLastTouchedWindow)
	{
		m_pLastTouchedWindow->OnTouchLost();
		m_pLastTouchedWindow = NULL;
	}

	bool bProcessed = false;

	switch (eType)
	{
	case UTET_BEGIN:
		{
			SetWindowState(WS_PRESSED, true);
			bProcessed = OnTouchBegin(pos);
		}
		break;
	case UTET_MOVE:
		{
			SetWindowState(WS_PRESSED, true);
			bProcessed = OnTouchMove(pos);
		}
		break;
	case UTET_END:
		{
			SetWindowState(WS_PRESSED, false);
			if (OnTouchEnd(pos)) bProcessed = true;
			if (OnClicked(pos)) bProcessed = true;
		}
		break;
	}

	return bProcessed;
}

bool UIWindow::EnumlateChildrenWindows(TV_WINDOW& vWindowsOut, IMsgHandler* pHandler, ENUM_WINDOW_FILTER pCallback, void* pCustomData)
{
	if (!pHandler || !pCallback) return false;

	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		bool bOK = (pHandler->*pCallback)(*it, pCustomData);
		if (bOK) vWindowsOut.push_back(*it);
	}

	return true;
}

void UIWindow::AddChild(UIWindow* pWindow)
{
	// check pWindow exist ?
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		if ((*it) == pWindow) return;
	}

	m_vChildren.push_back(pWindow);
}

void UIWindow::RemoveChild(UIWindow* pWindow)
{
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		if ((*it) == pWindow)
		{
			m_vChildren.erase(it);
			SAFE_RELEASE(pWindow);
			return;
		}
	}
}

void UIWindow::UpdateChildrenWindow(float dt)
{
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		pWindow->Update(dt);
	}
}

void UIWindow::RenderChildrenWindow(const RenderParam& param)
{
	RenderParam childParam = param;
	childParam.m_vBasePos += m_vPosition;
	childParam.m_vBaseSize = m_vSize;

	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		pWindow->Render(childParam);
	}
}

void UIWindow::RenderBorder(const RenderParam& param)
{
	Vector2 posAbs = param.m_vBasePos + GetPosition();
	const Vector2& size = GetSize();
	IRendererUI::GetInstance().DrawRect(posAbs, size, IUIResMgr::GetInstance().GetDefaultImageFrame());
}

bool UIWindow::OnClicked(const Vector2& pos)
{
	return true;
}

bool UIWindow::OnTouchBegin(const Vector2& pos)
{
	return true;
}

bool UIWindow::OnTouchMove(const Vector2& pos)
{
	return true;
}

bool UIWindow::OnTouchEnd(const Vector2& pos)
{
	return true;
}

void UIWindow::OnTouchLost()
{
	SetWindowState(WS_PRESSED, false);
}

UIWindow* UIWindow::FindChildUnderPoint(const Vector2& pos)
{
	for (TV_WINDOW::reverse_iterator it = m_vChildren.rbegin(); it != m_vChildren.rend(); ++it)
	{
		UIWindow* pWindow = (*it);
		if (PointInRect(pos, pWindow->GetPosition(), pWindow->GetSize())) return pWindow;
	}

	return NULL;
}
