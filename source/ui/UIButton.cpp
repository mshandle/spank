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

 	Vector2 posAbs = param.m_vBasePos + GetPosition();

	//calculate the off size of string 
	Vector2 vStrPosOff = (GetSize() - m_pString->GetSize());
	vStrPosOff.x = vStrPosOff.x / 2.0f;
	vStrPosOff.y = vStrPosOff.y / 2.0f;

	if (!IsEnable() || !param.IsEnable())
	{
		// render disabled state
		Vector2 vbutPosOff;
		vbutPosOff.x = (GetSize().x - m_pStyle[DUS_BUTTON_DISABLED]->width) / 2.0f;
		vbutPosOff.y = (GetSize().y - m_pStyle[DUS_BUTTON_DISABLED]->height) / 2.0f;
		IRendererUI::GetInstance().DrawRect(posAbs + vbutPosOff, m_pStyle[DUS_BUTTON_DISABLED]);
		// TODO: render string disabled state
		m_pString->Render(posAbs + vStrPosOff);
	}
	else if (IsPressed())
	{
		// render pressed state
		Vector2 vbutPosOff;
		vbutPosOff.x = (GetSize().x - m_pStyle[DUS_BUTTON_PRESSED]->width) / 2.0f;
		vbutPosOff.y = (GetSize().y - m_pStyle[DUS_BUTTON_PRESSED]->height) / 2.0f;
		IRendererUI::GetInstance().DrawRect(posAbs + vbutPosOff, m_pStyle[DUS_BUTTON_PRESSED]);
		// TODO: render string pressed state
		m_pString->Render(posAbs + vStrPosOff);
	}
	else
	{
		// render default state
		Vector2 vbutPosOff;
		vbutPosOff.x = (GetSize().x - m_pStyle[DUS_BUTTON_DEFAULT]->width) / 2.0f;
		vbutPosOff.y = (GetSize().y - m_pStyle[DUS_BUTTON_DEFAULT]->height) / 2.0f;
		IRendererUI::GetInstance().DrawRect(posAbs + vbutPosOff, m_pStyle[DUS_BUTTON_DEFAULT]);
		// TODO: render string pressed state
		m_pString->Render(posAbs + vStrPosOff);
	}
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
