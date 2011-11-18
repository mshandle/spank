/*!
 * \file UISliderBar.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UISliderBar.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <ui/IUISystem.h>
#include <ui/uimsg/MsgSlider.h>
#include <util/IDebugUtil.h>

UISliderBar::UISliderBar(UIWindow* pParent, const Vector2& pos /* = IMath::VEC2_ZERO */)
:UIWindow(pParent, pos)
{
	m_nMinRange = SLIDERBAR_MIN_RANGE;
	m_nMaxRange = SLIDERBAR_MAX_RANGE;
	m_nCurrentPos = SLIDERBAR_DEFAULT_POS;

	IUIResMgr::GetInstance().SetupDefaultSliderBarTextures(m_pStyle, DUS_SLIDERBAR_NUM);
	AdjustSize();
}

UISliderBar::~UISliderBar()
{
	// TODO: 
}

void UISliderBar::Update(float dt)
{
	// TODO: 
}

void UISliderBar::Render(const RenderParam& param)
{
	RenderBorder(param);

	Vector2 vRenderPos = param.m_renderOffset + GetPosition();
	UIRect dispRect(vRenderPos, GetSize());
	if (!IRendererUI::GetInstance().ClipRect(dispRect, param.m_parentRect)) return;

	// setup image piece
	const IMAGE_PIECE* pImagePieceThumb = m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT];
	const IMAGE_PIECE* pImagePieceBg = m_pStyle[DUS_SLIDERBAR_BACKGROUND];
	const IMAGE_PIECE* pImagePieceFg = m_pStyle[DUS_SLIDERBAR_FOREGROUND];
	if (!IsEnable() || !param.IsEnable())
	{
		pImagePieceThumb = m_pStyle[DUS_SLIDERBAR_THUMB_DISABLED];
	}
	else if (IsPressed())
	{
		pImagePieceThumb = m_pStyle[DUS_SLIDERBAR_THUMB_PRESSED];
	}

	// render background
	Vector2 vBgSize(pImagePieceBg->width, pImagePieceBg->height);
	Vector2 vBgPos = vRenderPos + (GetSize() - vBgSize) * 0.5f;
	vBgPos.x = vRenderPos.x;
	QUAD_VERT_POS_UV quad;
	IRendererUI::GetInstance().SetupQuad(quad, pImagePieceBg, vBgPos);
	if (IRendererUI::GetInstance().ClipRect(quad, dispRect.pos, dispRect.size))
	{
		IRendererUI::GetInstance().SetTexture(pImagePieceBg->pTexture);
		IRendererUI::GetInstance().DrawRect(quad);
	}

	float fAlpha = (float) m_nCurrentPos / (m_nMaxRange - m_nMinRange);

	//render the foreground
	if (fAlpha > 0.0f)
	{
		Vector2 vFgSize(fAlpha*pImagePieceFg->width, pImagePieceFg->height);
		IRendererUI::GetInstance().SetupQuad(quad, pImagePieceFg, vBgPos);
		if (IRendererUI::GetInstance().ClipRect(quad, vBgPos, vFgSize) && IRendererUI::GetInstance().ClipRect(quad, dispRect.pos, dispRect.size))
		{
			IRendererUI::GetInstance().SetTexture(pImagePieceFg->pTexture);
			IRendererUI::GetInstance().DrawRect(quad);
		}
	}

	// render the thumb
	Vector2 vThumbPos;
	vThumbPos.x = vRenderPos.x + fAlpha*GetSize().x - pImagePieceThumb->width / 2.0f;
	vThumbPos.y = vRenderPos.y + (GetSize().y - pImagePieceThumb->height) / 2.0f;
	IRendererUI::GetInstance().SetupQuad(quad, pImagePieceThumb, vThumbPos);
	if (IRendererUI::GetInstance().ClipRect(quad, dispRect.pos, dispRect.size))
	{
		IRendererUI::GetInstance().SetTexture(pImagePieceThumb->pTexture);
		IRendererUI::GetInstance().DrawRect(quad);
	}
}

Vector2 UISliderBar::GetBestSize()
{
	// calculate the boundary of the sliderbar
	Vector2 sizeMax = Vector2(m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width, m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height);
	if (sizeMax.x < m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width) sizeMax.x = m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width;

	if (sizeMax.y < m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height) sizeMax.y = m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height;
	if (sizeMax.y < m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height) sizeMax.y = m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height;

	return sizeMax;
}

bool UISliderBar::SetSliderRange(int nMinRange, int nMaxRange)
{
	if (nMinRange < 0 || nMaxRange < 0) return false;
	if (nMinRange > nMaxRange) return false;

	m_nMinRange = nMinRange;
	m_nMaxRange = nMaxRange;
	SetCurrentPos(m_nCurrentPos);

	return true;
}

void UISliderBar::SetCurrentPos(int nPos)
{
	m_nCurrentPos = nPos;
	if (m_nCurrentPos < m_nMinRange) m_nCurrentPos = m_nMinRange;
	if (m_nCurrentPos > m_nMaxRange) m_nCurrentPos = m_nMaxRange;
}

bool UISliderBar::SetSliderBarTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_SLIDERBAR_NUM) return false;

	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();
	return true;
}

bool UISliderBar::OnClicked(const Vector2& pos)
{
	m_nCurrentPos = CalculatePosition(pos, GetSize());
	MsgSlider msgSlider(MsgSlider::ST_POSITION, m_nCurrentPos, this);
	CallEvent(msgSlider);
	return true;
}

bool UISliderBar::OnTouchBegin(const Vector2& pos)
{
	IUISystem::GetInstance().CaptureMouse(this);
	return true;
}

bool UISliderBar::OnTouchMove(const Vector2& pos)
{
	m_nCurrentPos = CalculatePosition(pos, GetSize());
	MsgSlider msgSlider(MsgSlider::ST_TRACKING, m_nCurrentPos, this);
	CallEvent(msgSlider);
	return true;
}

bool UISliderBar::OnTouchEnd(const Vector2& pos)
{
	IUISystem::GetInstance().ReleaseMouse();
	return true;
}

int UISliderBar::CalculatePosition(const Vector2& posMouse, const Vector2& size)
{
	float fPos = posMouse.x;
	if (fPos < 0.0f) fPos = 0.0f;
	if (fPos > size.x) fPos = size.x;

	float fAlpha = fPos / size.x;
	return (int)(m_nMinRange + fAlpha*(m_nMaxRange-m_nMinRange) + 0.5f);
}
