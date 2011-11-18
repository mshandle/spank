/*!
 * \file UICheckButton.cpp
 * \date 2011/09/09 11:23
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UICheckButton.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <IResourceMgr.h>
#include <ui/uimsg/MsgCheck.h>

UICheckButton::UICheckButton(UIWindow* pParent, const Vector2& pos /* = IMath::VEC2_ZERO */, const char* pszText /* = NULL */)
:UIWindow(pParent, pos)
{
	m_pString = new UIString(pszText);
	m_bCheck = false;

	// load default state styles
	IUIResMgr::GetInstance().SetupDefaultCheckButtonTextures(m_pStyle);

	AdjustSize();
}

UICheckButton::~UICheckButton()
{
	SAFE_DELETE(m_pString);
}

void UICheckButton::Update(float dt)
{
	// TODO: 
}

void UICheckButton::Render(const RenderParam& param)
{
	RenderBorder(param);

	Vector2 vRenderPos = param.m_renderOffset + GetPosition();
	UIRect dispRect(vRenderPos, GetSize());
	if (!IRendererUI::GetInstance().ClipRect(dispRect, param.m_parentRect)) return;

	// setup image piece
	const IMAGE_PIECE* pImagePiece = m_pStyle[DUS_CHECKBUTTON_CHECK];
	if (IsChecked())
	{
		if (!IsEnable() || !param.IsEnable())
		{
			pImagePiece = m_pStyle[DUS_CHECKBUTTON_CHECK_DISABLED];
		}
		else if (IsPressed())
		{
			pImagePiece = m_pStyle[DUS_CHECKBUTTON_CHECK_PRESSED];
		}
		else
		{
			pImagePiece = m_pStyle[DUS_CHECKBUTTON_CHECK];
		}
	}
	else
	{
		if (!IsEnable() || !param.IsEnable())
		{
			pImagePiece = m_pStyle[DUS_CHECKBUTTON_UNCHECK_DISABLED];
		}
		else if (IsPressed())
		{
			pImagePiece = m_pStyle[DUS_CHECKBUTTON_UNCHECK_PRESSED];
		}
		else
		{
			pImagePiece = m_pStyle[DUS_CHECKBUTTON_UNCHECK];
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

Vector2 UICheckButton::GetBestSize()
{
	Vector2 sizeImage(m_pStyle[DUS_CHECKBUTTON_CHECK]->width, m_pStyle[DUS_CHECKBUTTON_CHECK]->height);
	const Vector2& sizeString = m_pString->GetSize();
	float width = sizeImage.x+sizeString.x;
	float height = sizeImage.y > sizeString.y ? sizeImage.y : sizeString.y;
	return Vector2(width, height);
}

void UICheckButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	AdjustSize();
}

bool UICheckButton::SetCheck(bool bCheck)
{
	if (m_bCheck == bCheck) return false;
	m_bCheck = bCheck;
	return true;
}

bool UICheckButton::IsChecked() const
{
	return m_bCheck;
}

bool UICheckButton::SetCheckButtonTexture(const char* pszImageId, int nIndex)
{
	return SetCheckButtonTexture(IResourceMgr::GetInstance().FindImagePiece(pszImageId), nIndex);
}

bool UICheckButton::SetCheckButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_CHECKBUTTON_NUM) return false;
	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();

	return true;
}

bool UICheckButton::OnClicked(const Vector2& pos)
{
	m_bCheck = !m_bCheck;
	// notify msg event
	MsgCheck msgCheck(m_bCheck, this);
	CallEvent(msgCheck);
	return true;
}
