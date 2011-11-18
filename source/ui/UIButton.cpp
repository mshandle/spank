/*!
 * \file UIButton.cpp
 * \date 2011/09/05 9:32
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIButton.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <ui/uimsg/MsgClick.h>
#include <ui/uimsg/UIMsgID.h>
#include <util/IDebugUtil.h>
#include <util/StringUtil.h>

UIButton::UIButton(UIWindow* pParent, const Vector2& pos /* = IMath::VEC2_ZERO */, const char* pszText /* = NULL */)
:UIWindow(pParent, pos)
{
	m_pString = new UIString(pszText);

	// load default state styles
	IUIResMgr::GetInstance().SetupDefaultButtonTextures(m_pStyle);

	AdjustSize();
}

UIButton::~UIButton()
{
	SAFE_DELETE(m_pString);
}

void UIButton::Update(float dt)
{
	// TODO: 
}

void UIButton::Render(const RenderParam& param)
{
	RenderBorder(param);

 	Vector2 vRenderPos = param.m_renderOffset + GetPosition();
	UIRect dispRect(vRenderPos, GetSize());
	if (!IRendererUI::GetInstance().ClipRect(dispRect, param.m_parentRect)) return;

	// setup image piece
	const IMAGE_PIECE* pImagePiece = m_pStyle[DUS_BUTTON_DEFAULT];
	if (!IsEnable() || !param.IsEnable())
	{
		pImagePiece = m_pStyle[DUS_BUTTON_DISABLED];
	}
	else if (IsPressed())
	{
		pImagePiece = m_pStyle[DUS_BUTTON_PRESSED];
	}

	// render button image
	Vector2 vImageSize(pImagePiece->width, pImagePiece->height);
	Vector2 vImagePos = vRenderPos + (GetSize() - vImageSize) * 0.5f;
	QUAD_VERT_POS_UV quad;
	IRendererUI::GetInstance().SetupQuad(quad, pImagePiece, vImagePos);
	if (IRendererUI::GetInstance().ClipRect(quad, dispRect.pos, dispRect.size))
	{
		IRendererUI::GetInstance().SetTexture(pImagePiece->pTexture);
		IRendererUI::GetInstance().DrawRect(quad);
	}

	//calculate the off size of string
	Vector2 vTextPos = vRenderPos + (GetSize() - m_pString->GetSize()) * 0.5f;
	// TODO: render string disabled state
	m_pString->Render(vTextPos, dispRect.pos, dispRect.size);
}

Vector2 UIButton::GetBestSize()
{
	Vector2 sizeMax = m_pString->GetSize();
	if (sizeMax.x < m_pStyle[DUS_BUTTON_DEFAULT]->width) sizeMax.x = m_pStyle[DUS_BUTTON_DEFAULT]->width;
	if (sizeMax.y < m_pStyle[DUS_BUTTON_DEFAULT]->height) sizeMax.y = m_pStyle[DUS_BUTTON_DEFAULT]->height;
	return sizeMax;
}

void UIButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	AdjustSize();
}

bool UIButton::SetButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_BUTTON_NUM) return false;

	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();

	return true;
}

bool UIButton::OnClicked(const Vector2& pos)
{
	MsgClick msgclick(this);
	CallEvent(msgclick);
	return true;
}
