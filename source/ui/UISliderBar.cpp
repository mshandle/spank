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

	Vector2 posAbs = param.m_vBasePos + GetPosition();

	//AdjustPosition
	if (m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height > m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height)
	{
		posAbs.y = posAbs.y + (m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height - m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height) /2.0f;
	}

	if (!IsEnable() || !param.IsEnable())
	{
		//render disabled state;
		IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_SLIDERBAR_THUMB_DISABLED]);
	}
	else
	{
		//render the background
		IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_SLIDERBAR_BACKGROUND]);

		//render the foreground
		QUAD_VERT_POS_UV quad;
		IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_SLIDERBAR_FOREGROUND], posAbs);
		IRendererUI::GetInstance().SetTexture(m_pStyle[DUS_SLIDERBAR_FOREGROUND]->pTexture);
		//calculate the size of the new foreground to render
		float fAlpha = (float) m_nCurrentPos / (m_nMaxRange - m_nMinRange);
		if (IRendererUI::GetInstance().ClipRect(quad, posAbs.x, posAbs.y, fAlpha*m_pStyle[DUS_SLIDERBAR_FOREGROUND]->width, m_pStyle[DUS_SLIDERBAR_FOREGROUND]->height))
		{	
			IRendererUI::GetInstance().DrawRect(quad);
		}
	
		if (IsPressed())
		{
			// render pressed state
			//calculate the position of the Arrow to render
			float fposx = posAbs.x + m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width * fAlpha - m_pStyle[DUS_SLIDERBAR_THUMB_PRESSED]->width / 2.0f;
			float fposy = posAbs.y - (m_pStyle[DUS_SLIDERBAR_THUMB_PRESSED]->height - m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height) / 2.0f;
			IRendererUI::GetInstance().DrawRect(fposx, fposy, m_pStyle[DUS_SLIDERBAR_THUMB_PRESSED]);
		}
		else
		{
			// render default state
			//calculate the position of the Arrow to render
			float fposx = posAbs.x + m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width * fAlpha - m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->width / 2.0f;
			float fposy = posAbs.y - (m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height - m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height) / 2.0f;
			IRendererUI::GetInstance().DrawRect(fposx, fposy, m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]);
		}
	}
}

Vector2 UISliderBar::GetBestSize()
{
	// TODO: calculate the boundary of the sliderbar
	Vector2 sizeMax = Vector2(m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width, m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height);
	if (sizeMax.x < m_pStyle[DUS_SLIDERBAR_FOREGROUND]->width) sizeMax.x = m_pStyle[DUS_SLIDERBAR_FOREGROUND]->width;
	if (sizeMax.y < m_pStyle[DUS_SLIDERBAR_FOREGROUND]->height) sizeMax.y = m_pStyle[DUS_SLIDERBAR_FOREGROUND]->height;
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
