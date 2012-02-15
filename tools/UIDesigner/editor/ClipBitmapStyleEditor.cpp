/*!
 * \file ClipBitmapStyleEditor.cpp
 * \date 2-15-2012 11:01:35
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ClipBitmapStyleEditor.h"

ClipBitmapStyleEditor* ClipBitmapStyleEditor::m_pClipBitmapStyleEditor = NULL;

ClipBitmapStyleEditor::ClipBitmapStyleEditor()
:BaseEditor()
{
	Init();
}

ClipBitmapStyleEditor::ClipBitmapStyleEditor(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
:BaseEditor(parent, winid, pos, size, style, name)
{
	Init();
}

ClipBitmapStyleEditor::~ClipBitmapStyleEditor()
{
	Release();
}

void ClipBitmapStyleEditor::Init()
{
	m_pClipBitmapStyleEditor = this;
	m_pClipBitmapStyle = NULL;
	m_eSelState = IStyle::SS_NUM;
}

void ClipBitmapStyleEditor::Release()
{
	m_pClipBitmapStyleEditor = NULL;
}

ClipBitmapStyleEditor& ClipBitmapStyleEditor::GetInstance()
{
	return *m_pClipBitmapStyleEditor;
}

bool ClipBitmapStyleEditor::SetClipBitmapStyle(const ClipBitmapStyle* pClipBitmapStyle)
{
	if (m_pClipBitmapStyle == pClipBitmapStyle) return false;
	m_pClipBitmapStyle = pClipBitmapStyle;

	UpdateSubBitmap();
	UpdateSubBitmapRect();

	SetSelState(IStyle::SS_NUM);
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	return true;
}

const ClipBitmapStyle* ClipBitmapStyleEditor::GetClipBitmapStyle() const
{
	return m_pClipBitmapStyle;
}

wxSize ClipBitmapStyleEditor::CalculateVirtualSize()
{
	return m_TotalSize;
}

void ClipBitmapStyleEditor::Draw(wxDC& dc)
{
	if (!m_pClipBitmapStyle) return;

	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		DrawBitmap(dc, m_bmpState[i], m_rectState[i].GetPosition());
	}

	DrawSelection(dc);
}

void ClipBitmapStyleEditor::DrawSelection(wxDC& dc)
{
	if (m_eSelState < 0 || m_eSelState >= IStyle::SS_NUM) return;
	dc.SetPen(*wxRED_PEN);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	DrawRectangle(dc, m_rectState[m_eSelState]);
}

void ClipBitmapStyleEditor::OnLButtonDown(const wxPoint& pos)
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

void ClipBitmapStyleEditor::SetSelState(IStyle::STYLE_STATE eState)
{
	m_eSelState = eState;
	Refresh(false);
}

IStyle::STYLE_STATE ClipBitmapStyleEditor::GetSelState() const
{
	return m_eSelState;
}

void ClipBitmapStyleEditor::UpdateSubBitmap()
{
	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		if (m_pClipBitmapStyle)
		{
			const PieceInfo* pPieceInfo = m_pClipBitmapStyle->GetStatePiece((IStyle::STYLE_STATE)i);
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

void ClipBitmapStyleEditor::UpdateSubBitmapRect()
{
	wxRect subRect(0, 0, 0, 0);
	m_TotalSize.x = 0;
	m_TotalSize.y = 0;

	for (int i = 0; i < IStyle::SS_NUM; ++i)
	{
		if (m_pClipBitmapStyle)
		{
			const PieceInfo* pPieceInfo = m_pClipBitmapStyle->GetStatePiece((IStyle::STYLE_STATE)i);
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
