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
	UpdateVirtualPosAndSize();
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
// 	RenderBorder(param);
	RenderChildrenWindow(param);
}

void UIScrollWindow::SetSize(float width, float height)
{
	UIWindow::SetSize(width, height);
	UpdateVirtualPosAndSize();
}

Vector2 UIScrollWindow::GetBestSize()
{
	return m_vVirtualRect.size;
}

bool UIScrollWindow::ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType)
{
	bool bProcessed = false;

	switch (eType)
	{
	case UTET_BEGIN:
		{
			SetWindowState(WS_PRESSED, true);
			bProcessed = OnTouchBegin(pos);
			// save the touch position
			m_vTouchPos = pos;
			m_vScrollOffsetBackup = m_vScrollOffset;
			IUISystem::GetInstance().CaptureMouse(this);
		}
		break;
	case UTET_MOVE:
		{
			SetWindowState(WS_PRESSED, true);
			bProcessed = OnTouchMove(pos);
			// calculate the offset
			m_vScrollOffset = m_vScrollOffsetBackup + pos - m_vTouchPos;
		}
		break;
	case UTET_END:
		{
			SetWindowState(WS_PRESSED, false);
			if (OnTouchEnd(pos)) bProcessed = true;
			if (OnClicked(pos)) bProcessed = true;
			m_vScrollOffsetBackup = IMath::VEC2_ZERO;
			IUISystem::GetInstance().ReleaseMouse();
		}
		break;
	}

	return bProcessed;
}

void UIScrollWindow::AddChild(UIWindow* pWindow)
{
	UIWindow::AddChild(pWindow);
	UpdateVirtualPosAndSize();
}

void UIScrollWindow::RemoveChild(UIWindow* pWindow)
{
	UIWindow::RemoveChild(pWindow);
	UpdateVirtualPosAndSize();
}

void UIScrollWindow::UpdateVirtualPosAndSize()
{
	Vector2 vLeftTop = IMath::VEC2_ZERO;
	Vector2 vRightBottom = IMath::VEC2_ZERO;

	TV_WINDOW& vChildren = UIWindow::GetChildrenList();
	for (TV_WINDOW::iterator it = vChildren.begin(); it != vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		const Vector2& leftTop = pWindow->GetPosition();
		Vector2 rightBottom = leftTop + pWindow->GetSize();

		if (leftTop.x < vLeftTop.x) vLeftTop.x = leftTop.x;
		if (leftTop.y < vLeftTop.y) vLeftTop.y = leftTop.y;
		if (rightBottom.x > vRightBottom.x) vRightBottom.x = rightBottom.x;
		if (rightBottom.y > vRightBottom.y) vRightBottom.y = rightBottom.y;
	}

	const Vector2& vSize = GetSize();

	if (vLeftTop.x > 0) vLeftTop.x = 0;
	if (vLeftTop.y > 0) vLeftTop.y = 0;
	if (vRightBottom.x < vSize.x) vRightBottom.x = vSize.x;
	if (vRightBottom.y < vSize.y) vRightBottom.y = vSize.y;

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
