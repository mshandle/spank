/*!
 * \file UIRadioButton.cpp
 * \date 2011/09/08 10:17
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIRadioButton.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <ui/uimsg/MsgCheck.h>
#include <IResourceMgr.h>

UIRadioButton::UIRadioButton(UIWindow* pParent, const Vector2& pos /* = IMath::VEC2_ONE */, const char* pszText /* = NULL */)
:UIWindow(pParent, pos)
{
	m_nGroupID = 1;
	m_pString = new UIString(pszText);
	m_bCheck = false;

	IUIResMgr::GetInstance().SetupDefaultRadioButtonTextures(m_pStyle, DUS_RADIOBUTTON_NUM);

	AdjustSize();
}

UIRadioButton::~UIRadioButton()
{
	SAFE_DELETE(m_pString);
}

void UIRadioButton::Update(float dt)
{
	// TODO: 
}

void UIRadioButton::Render(const RenderParam& param)
{
	RenderBorder(param);

	Vector2 vRenderPos = param.m_renderOffset + GetPosition();
	UIRect dispRect(vRenderPos, GetSize());
	if (!IRendererUI::GetInstance().ClipRect(dispRect, param.m_parentRect)) return;

	// setup image piece
	const IMAGE_PIECE* pImagePiece = m_pStyle[DUS_RADIOBUTTON_CHECK];
	if (IsChecked())
	{
		if (!IsEnable() || !param.IsEnable())
		{
			pImagePiece = m_pStyle[DUS_RADIOBUTTON_CHECK_DISABLED];
		}
		else if (IsPressed())
		{
			pImagePiece = m_pStyle[DUS_RADIOBUTTON_CHECK_PRESSED];
		}
		else
		{
			pImagePiece = m_pStyle[DUS_RADIOBUTTON_CHECK];
		}
	}
	else
	{
		if (!IsEnable() || !param.IsEnable())
		{
			pImagePiece = m_pStyle[DUS_RADIOBUTTON_UNCHECK_DISABLED];
		}
		else if (IsPressed())
		{
			pImagePiece = m_pStyle[DUS_RADIOBUTTON_UNCHECK_PRESSED];
		}
		else
		{
			pImagePiece = m_pStyle[DUS_RADIOBUTTON_UNCHECK];
		}
	}

	// render button image
	Vector2 vImageSize(pImagePiece->width, pImagePiece->height);
	Vector2 vImagePos = vRenderPos + (GetSize() - vImageSize) * 0.5f;
	vImagePos.x = vRenderPos.x;
	QUAD_VERT_POS_UV quad;
	IRendererUI::GetInstance().SetupQuad(quad, pImagePiece, vImagePos);
	if (IRendererUI::GetInstance().ClipRect(quad, dispRect.pos, dispRect.size))
	{
		IRendererUI::GetInstance().SetTexture(pImagePiece->pTexture);
		IRendererUI::GetInstance().DrawRect(quad);
	}

	//calculate the off size of string in the right;
	Vector2 vTextPos = vRenderPos + (GetSize() - m_pString->GetSize()) * 0.5f;
	vTextPos.x = vRenderPos.x + vImageSize.x;
	// TODO: render string disabled state
	m_pString->Render(vTextPos, dispRect.pos, dispRect.size);
}

Vector2 UIRadioButton::GetBestSize()
{
	Vector2 sizeImage(m_pStyle[DUS_RADIOBUTTON_CHECK]->width, m_pStyle[DUS_RADIOBUTTON_CHECK]->height);
	const Vector2& sizeString = m_pString->GetSize();
	float width = sizeImage.x+sizeString.x;
	float height = sizeImage.y > sizeString.y ? sizeImage.y : sizeString.y;
	return Vector2(width, height);
}

void UIRadioButton::SetGroupID(int nGroup)
{
	m_nGroupID = nGroup;

	// join to a new group
	if(!IsChecked()) return;

	UIWindow* pParentWindow = GetParentWindow();
	if (!pParentWindow) return;

	TV_WINDOW vRadioButton;
	if (!pParentWindow->EnumlateChildrenWindows(vRadioButton, this, (ENUM_WINDOW_FILTER)&UIRadioButton::RadioButtonFilter, NULL)) return;

	for (TV_WINDOW::iterator it = vRadioButton.begin(); it != vRadioButton.end(); ++it)
	{
		UIRadioButton* pRadioButton = (UIRadioButton*)(*it);
		if (pRadioButton->IsChecked())
		{
			SetCheck(false);
			return;
		}
	}
}

int UIRadioButton::GetGroupID() const
{
	return m_nGroupID;
}

void UIRadioButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	AdjustSize();
}

bool UIRadioButton::SetCheck(bool bCheck)
{
	if (m_bCheck == bCheck) return false;
	m_bCheck = bCheck;
	if (!m_bCheck) return true;

	// remove the old check one
	UIWindow* pParentWindow = GetParentWindow();
	if (!pParentWindow) return true;

	TV_WINDOW vRadioButton;
	if (!pParentWindow->EnumlateChildrenWindows(vRadioButton, this, (ENUM_WINDOW_FILTER)&UIRadioButton::RadioButtonFilter, NULL)) return true;

	for (TV_WINDOW::iterator it = vRadioButton.begin(); it != vRadioButton.end(); ++it)
	{
		UIRadioButton* pRadioButton = (UIRadioButton*)(*it);
		pRadioButton->SetCheck(false);
	}

	return true;
}

bool UIRadioButton::IsChecked() const
{
	return m_bCheck;
}

bool UIRadioButton::SetRadioButtonTexture(const char* pszImageId, int nIndex)
{
	return SetRadioButtonTexture(IResourceMgr::GetInstance().FindImagePiece(pszImageId), nIndex);
}

bool UIRadioButton::SetRadioButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_RADIOBUTTON_NUM) return false;
	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();

	return true;
}

bool UIRadioButton::OnClicked(const Vector2& pos)
{
	// change status and send message
	if (SetCheck(true))
	{
		MsgCheck msgCheck(m_bCheck, this);
		CallEvent(msgCheck);
	}
	return true;
}

bool UIRadioButton::RadioButtonFilter(UIWindow* pWindow, void* pData)
{
	if (pWindow == this) return false;
	if (pWindow->GetRtti() != this->GetRtti()) return false;

	UIRadioButton* pRadioButton = (UIRadioButton*)pWindow;
	if (pRadioButton->GetGroupID() != this->GetGroupID()) return false;
	
	return true;
}
