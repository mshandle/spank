/*!
 * \file NineGridStyleEditor.cpp
 * \date 2-15-2012 12:45:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NineGridStyleEditor.h"

NineGridStyleEditor* NineGridStyleEditor::m_pNineGridStyleEditor = NULL;

NineGridStyleEditor::NineGridStyleEditor()
:BaseEditor()
{
	Init();
}

NineGridStyleEditor::NineGridStyleEditor(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
:BaseEditor(parent, winid, pos, size, style, name)
{
	Init();
}

NineGridStyleEditor::~NineGridStyleEditor()
{
	Release();
}

void NineGridStyleEditor::Init()
{
	m_pNineGridStyleEditor = this;
	m_pNineGridStyle = NULL;
}

void NineGridStyleEditor::Release()
{
	m_pNineGridStyleEditor = NULL;
}

NineGridStyleEditor& NineGridStyleEditor::GetInstance()
{
	return *m_pNineGridStyleEditor;
}

bool NineGridStyleEditor::SetNineGridStyle(NineGridStyle* pNineGridStyle)
{
	if (m_pNineGridStyle == pNineGridStyle) return false;
	m_pNineGridStyle = pNineGridStyle;

	UpdateSubBitmap();
	UpdateSubBitmapRect();

	SetSelState(IStyle::SS_NUM);

	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	return true;
}

NineGridStyle* NineGridStyleEditor::GetNineGridStyle()
{
	return m_pNineGridStyle;
}

wxSize NineGridStyleEditor::CalculateVirtualSize()
{
	return m_TotalSize;
}

void NineGridStyleEditor::Draw(wxDC& dc)
{
	if (!m_pNineGridStyle) return;

	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		DrawBitmap(dc, m_bmpState[i], m_rectState[i].GetPosition());
	}

	DrawSelection(dc);
}

void NineGridStyleEditor::DrawSelection(wxDC& dc)
{
	if (m_eSelState < 0 || m_eSelState >= IStyle::SS_NUM) return;

	const wxRect& rect = m_rectState[m_eSelState];

	dc.SetPen(*wxRED_PEN);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	DrawRectangle(dc, rect);

	wxSize maxSize = CalculateMaxSize();
	NineGridStyle::NINE_GRID_INFO* pGridInfo = m_pNineGridStyle->GetStateGridInfo(m_eSelState);

	dc.SetPen(*wxBLUE_PEN);
	if (pGridInfo->min_y != pGridInfo->max_y)
	{
		DrawLine(dc, wxPoint(0, rect.y+pGridInfo->min_y), wxPoint(maxSize.x, rect.y+pGridInfo->min_y));
		DrawLine(dc, wxPoint(0, rect.y+pGridInfo->max_y), wxPoint(maxSize.x, rect.y+pGridInfo->max_y));
	}
	if (pGridInfo->min_x != pGridInfo->max_x)
	{
		DrawLine(dc, wxPoint(rect.x+pGridInfo->min_x, 0), wxPoint(rect.x+pGridInfo->min_x, maxSize.y));
		DrawLine(dc, wxPoint(rect.x+pGridInfo->max_x, 0), wxPoint(rect.x+pGridInfo->max_x, maxSize.y));
	}
}

void NineGridStyleEditor::OnLButtonDown(const wxPoint& pos)
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

void NineGridStyleEditor::SetSelState(IStyle::STYLE_STATE eState)
{
	m_eSelState = eState;
	Refresh(false);
}

IStyle::STYLE_STATE NineGridStyleEditor::GetSelState() const
{
	return m_eSelState;
}

void NineGridStyleEditor::UpdateSubBitmap()
{
	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		if (m_pNineGridStyle)
		{
			PieceInfo* pPieceInfo = m_pNineGridStyle->GetStateGridInfo((IStyle::STYLE_STATE)i)->pPieceInfo;
			const wxRect& pieceRect = pPieceInfo->GetRect();
			wxBitmap* pMainBitmap = pPieceInfo->GetImageInfo()->GetBitmap();
			m_bmpState[i] = pMainBitmap->GetSubBitmap(pieceRect);
		}
		else
		{
			m_bmpState[i] = wxNullBitmap;
		}
	}
}

void NineGridStyleEditor::UpdateSubBitmapRect()
{
	wxRect subRect(0, 0, 0, 0);
	m_TotalSize.x = 0;
	m_TotalSize.y = 0;

	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		if (m_pNineGridStyle)
		{
			PieceInfo* pPieceInfo = m_pNineGridStyle->GetStateGridInfo((IStyle::STYLE_STATE)i)->pPieceInfo;
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
