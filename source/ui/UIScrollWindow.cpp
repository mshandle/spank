/*!
 * \file UIScrollWindow.cpp
 * \date 11-18-2011 9:07:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIScrollWindow.h>
#include <ui/IUISystem.h>
#include <ui/IRendererUI.h>
#include <IResourceMgr.h>

UIScrollWindow::UIScrollWindow(UIWindow* pParent, const Vector2& pos /*= IMath::VEC2_ZERO*/)
:UIWindow(pParent, pos)
{
	m_vScrollOffset = IMath::VEC2_ZERO;
	m_vScrollOffsetBackup = IMath::VEC2_ZERO;
	m_vTouchPos = IMath::VEC2_ZERO;
	m_vVirtualRect = UIRect::UIRECT_ZERO;
	m_pLastTouchedWindow = NULL;
	m_nScrollWindowFlag = SWS_DEFAULT;
}

UIScrollWindow::~UIScrollWindow()
{
	// TODO: 
}

void UIScrollWindow::Update(float dt)
{
	// TODO: 
}

void UIScrollWindow::Render(const RenderParam& param)
{
//  	RenderBorder(param);
	RenderChildrenWindow(param);
}

Vector2 UIScrollWindow::GetBestSize()
{
	return GetSize();
}

bool UIScrollWindow::ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType)
{
	Vector2 localPos = pos - m_vScrollOffset;
	UIWindow* pWindow = FindChildUnderPoint(localPos);

	bool bProcessed = false;
	switch (eType)
	{
	case UTET_BEGIN:
		{
			// save the touch position
			m_vTouchPos = pos;
			m_vScrollOffsetBackup = m_vScrollOffset;
			SetScrollWindowState(SWS_MOUSE_MOVED, false);

			if (pWindow)
			{
				if (m_pLastTouchedWindow && m_pLastTouchedWindow != pWindow) m_pLastTouchedWindow->OnTouchLost();
				m_pLastTouchedWindow = pWindow;

				Vector2 childPos = localPos - pWindow->GetPosition();
				return pWindow->ProcessTouchEvent(childPos, eType);
			}

			if (m_pLastTouchedWindow)
			{
				m_pLastTouchedWindow->OnTouchLost();
				m_pLastTouchedWindow = NULL;
			}

			SetWindowState(WS_PRESSED, true);
			bProcessed = OnTouchBegin(pos);
		}
		break;
	case UTET_MOVE:
		{
			SetScrollWindowState(SWS_MOUSE_MOVED, true);
			if (m_pLastTouchedWindow)
			{
				m_pLastTouchedWindow->OnTouchLost();
				m_pLastTouchedWindow = NULL;
			}

			// calculate the offset

			if (CheckScrollWindowState(SWS_VSCROLL))
			{
				m_vScrollOffset.y = m_vScrollOffsetBackup.y + pos.y - m_vTouchPos.y;
			}

			if (CheckScrollWindowState(SWS_HSCROLL))
			{
				m_vScrollOffset.x = m_vScrollOffsetBackup.x + pos.x - m_vTouchPos.x;
			}

			SetWindowState(WS_PRESSED, true);
			bProcessed = OnTouchMove(pos);
		}
		break;
	case UTET_END:
		{
			if (CheckScrollWindowState(SWS_MOUSE_MOVED))
			{
				SetScrollWindowState(SWS_MOUSE_MOVED, false);
				SetWindowState(WS_PRESSED, false);
				if (OnTouchEnd(pos)) bProcessed = true;
				if (OnClicked(pos)) bProcessed = true;
				m_vScrollOffsetBackup = IMath::VEC2_ZERO;
			}
			else
			{
				if (pWindow)
				{
					if (m_pLastTouchedWindow && m_pLastTouchedWindow != pWindow) m_pLastTouchedWindow->OnTouchLost();
					m_pLastTouchedWindow = pWindow;

					Vector2 childPos = localPos - pWindow->GetPosition();
					return pWindow->ProcessTouchEvent(childPos, eType);
				}

				if (m_pLastTouchedWindow)
				{
					m_pLastTouchedWindow->OnTouchLost();
					m_pLastTouchedWindow = NULL;
				}
			}
		}
		break;
	}

	return bProcessed;
}

void UIScrollWindow::SetScrollWindowState(uint nMask, bool bSet)
{
	if (bSet)
	{
		m_nScrollWindowFlag |= nMask;
	}
	else
	{
		m_nScrollWindowFlag &= (~nMask);
	}
}

bool UIScrollWindow::CheckScrollWindowState(uint nMask) const
{
	return (m_nScrollWindowFlag & nMask) == nMask;
}

void UIScrollWindow::UpdateVirtualRect()
{
	Vector2 vLeftTop = IMath::VEC2_MAX;
	Vector2 vRightBottom = IMath::VEC2_MIN;

	TV_WINDOW& vChildren = UIWindow::GetChildrenList();
	for (TV_WINDOW::iterator it = vChildren.begin(); it != vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		const Vector2& leftTop = pWindow->GetPosition();
		Vector2 rightBottom = leftTop + pWindow->GetSize();

		if (vLeftTop.x > leftTop.x) vLeftTop.x = leftTop.x;
		if (vLeftTop.y > leftTop.y) vLeftTop.y = leftTop.y;
		if (vRightBottom.x < rightBottom.x) vRightBottom.x = rightBottom.x;
		if (vRightBottom.y < rightBottom.y) vRightBottom.y = rightBottom.y;
	}

	m_vVirtualRect.pos = vLeftTop;
	m_vVirtualRect.size = vRightBottom - vLeftTop;
}

void UIScrollWindow::RenderChildrenWindow(const RenderParam& param)
{
	RenderParam childParam;
	childParam.m_renderOffset = param.m_renderOffset + GetPosition() + m_vScrollOffset;
	childParam.m_parentRect.SetRect(param.m_renderOffset + GetPosition(), GetSize());
	childParam.m_nRenderState = param.m_nRenderState;

	TV_WINDOW& vChildren = UIWindow::GetChildrenList();
	for (TV_WINDOW::iterator it = vChildren.begin(); it != vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		pWindow->Render(childParam);
	}
}

void UIScrollWindow::RenderBorder(const RenderParam& param)
{
 	Vector2 posAbs = param.m_renderOffset + GetPosition() + m_vScrollOffset;
 	const Vector2& size = GetSize();

	QUAD_VERT_POS_UV quad;
	const IMAGE_PIECE* pPiece = IResourceMgr::GetInstance().FindImagePiece("ui_button_default");
	IRendererUI::GetInstance().SetupQuad(quad, pPiece, posAbs, size);
	if (IRendererUI::GetInstance().ClipRect(quad, param.m_renderOffset + GetPosition(), GetSize()))
	{
		IRendererUI::GetInstance().SetTexture(pPiece->pTexture);
		IRendererUI::GetInstance().DrawRect(quad);
	}
}
