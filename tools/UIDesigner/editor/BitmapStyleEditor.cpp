/*!
 * \file BitmapStyleEditor.cpp
 * \date 2-15-2012 11:01:35
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapStyleEditor.h"

BitmapStyleEditor* BitmapStyleEditor::m_pBitmapStyleEditor = NULL;

BitmapStyleEditor::BitmapStyleEditor()
:BaseEditor()
{
	Init();
}

BitmapStyleEditor::BitmapStyleEditor(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
:BaseEditor(parent, winid, pos, size, style, name)
{
	Init();
}

BitmapStyleEditor::~BitmapStyleEditor()
{
	Release();
}

void BitmapStyleEditor::Init()
{
	m_pBitmapStyleEditor = this;
	m_pBitmapStyle = NULL;
	m_eSelState = IStyle::SS_NUM;
}

void BitmapStyleEditor::Release()
{
	m_pBitmapStyleEditor = NULL;
}

BitmapStyleEditor& BitmapStyleEditor::GetInstance()
{
	return *m_pBitmapStyleEditor;
}

bool BitmapStyleEditor::SetBitmapStyle(const BitmapStyle* pBitmapStyle)
{
	if (m_pBitmapStyle == pBitmapStyle) return false;
	m_pBitmapStyle = pBitmapStyle;

	UpdateSubBitmap();
	UpdateSubBitmapRect();

	SetSelState(IStyle::SS_NUM);
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	return true;
}

const BitmapStyle* BitmapStyleEditor::GetBitmapStyle()
{
	return m_pBitmapStyle;
}

wxSize BitmapStyleEditor::CalculateVirtualSize()
{
	return m_TotalSize;
}

void BitmapStyleEditor::Draw(wxDC& dc)
{
	if (!m_pBitmapStyle) return;

	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		DrawBitmap(dc, m_bmpState[i], m_rectState[i].GetPosition());
	}

	DrawSelection(dc);
}

void BitmapStyleEditor::DrawSelection(wxDC& dc)
{
	if (m_eSelState < 0 || m_eSelState >= IStyle::SS_NUM) return;
	dc.SetPen(*wxRED_PEN);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	DrawRectangle(dc, m_rectState[m_eSelState]);
}

void BitmapStyleEditor::OnLButtonDown(const wxPoint& pos)
{
	wxPoint posOrigin = (pos + GetOriginOffset()) / GetZoom();
	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		if (m_rectState[i].Contains(posOrigin))
		{
			// set selection
			SetSelState((IStyle::STYLE_STATE)i);
			return;
		}
	}

	SetSelState(IStyle::SS_NUM);
}

void BitmapStyleEditor::SetSelState(IStyle::STYLE_STATE eState)
{
	m_eSelState = eState;
	Refresh(false);
}

IStyle::STYLE_STATE BitmapStyleEditor::GetSelState() const
{
	return m_eSelState;
}

void BitmapStyleEditor::UpdateSubBitmap()
{
	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		if (m_pBitmapStyle)
		{
			const PieceInfo* pPieceInfo = m_pBitmapStyle->GetStatePiece((IStyle::STYLE_STATE)i);
			const wxRect& pieceRect = pPieceInfo->GetRect();
			ImageInfo* pImageInfo = (ImageInfo*)pPieceInfo->GetImageInfo();
			const wxBitmap* pMainBitmap = pImageInfo->GetBitmap();
			m_bmpState[i] = pMainBitmap->GetSubBitmap(pieceRect);
		}
		else
		{
			m_bmpState[i] = wxNullBitmap;
		}
	}
}

void BitmapStyleEditor::UpdateSubBitmapRect()
{
	wxRect subRect(0, 0, 0, 0);
	m_TotalSize.x = 0;
	m_TotalSize.y = 0;

	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		if (m_pBitmapStyle)
		{
			const PieceInfo* pPieceInfo = m_pBitmapStyle->GetStatePiece((IStyle::STYLE_STATE)i);
			const wxRect& pieceRect = pPieceInfo->GetRect();

			subRect.width = pieceRect.width;
			subRect.height = pieceRect.height;

			m_rectState[i] = subRect;

			subRect.x = 0;
			subRect.y += subRect.height;

			if (m_TotalSize.x < pieceRect.width) m_TotalSize.x = pieceRect.width;
			m_TotalSize.y += pieceRect.height;
		}
		else
		{
			m_rectState[i] = subRect;
		}
	}
}
