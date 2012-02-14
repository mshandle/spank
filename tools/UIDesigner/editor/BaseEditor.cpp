/*!
 * \file BaseEditor.cpp
 * \date 2-14-2012 17:59:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BaseEditor.h"
#include <wx/dcclient.h>

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

BEGIN_EVENT_TABLE(BaseEditor, wxWindow)
	EVT_PAINT(BaseEditor::OnPaint)
	EVT_MOUSEWHEEL(BaseEditor::OnMouseWheel)
	EVT_LEFT_DOWN(BaseEditor::OnMouseLButtonDown)
	EVT_SIZE(BaseEditor::OnSize)
	EVT_SCROLLWIN_LINEUP(BaseEditor::OnScrollLineUp)
	EVT_SCROLLWIN_LINEDOWN(BaseEditor::OnScrollLineDown)
	EVT_SCROLLWIN_PAGEUP(BaseEditor::OnScrollPageUp)
	EVT_SCROLLWIN_PAGEDOWN(BaseEditor::OnScrollPageDown)
	EVT_SCROLLWIN_THUMBTRACK(BaseEditor::OnScrollThumbTrack)
	EVT_SCROLLWIN_THUMBRELEASE(BaseEditor::OnScrollThumbRelease)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(BaseEditor, wxWindow)

BaseEditor::BaseEditor()
{
	Init();
}

BaseEditor::BaseEditor(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
{
	Init();
	Create(parent, winid, pos, size, style, name);
}

BaseEditor::~BaseEditor()
{
	Release();
}

void BaseEditor::Init()
{
	m_nZoom = ZOOM_MIN;

	m_sizeVirtual.Set(DEFAULT_VIRTUAL_SIZE*m_nZoom, DEFAULT_VIRTUAL_SIZE*m_nZoom);
	m_ptOrigin.x = 0;
	m_ptOrigin.y = 0;
}

void BaseEditor::Release()
{
	// TODO: 
}

bool BaseEditor::Create(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
{
	if (!wxWindow::Create(parent, winid, pos, size, style, name)) return false;

	return true;
}

wxSize BaseEditor::DoGetBestSize() const
{
	return m_sizeVirtual;
}

bool BaseEditor::ZoomIn()
{
	return Zoom(m_nZoom+1);
}

bool BaseEditor::ZoomOut()
{
	return Zoom(m_nZoom-1);
}

bool BaseEditor::Zoom(int zoom)
{
	if (zoom < ZOOM_MIN || zoom > ZOOM_MAX) return false;
	if (m_nZoom == zoom) return true;

	m_ptOrigin = (m_ptOrigin/m_nZoom)*zoom;
	m_nZoom = zoom;
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));

	return true;
}

int BaseEditor::GetZoom() const
{
	return m_nZoom;
}

void BaseEditor::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	// get client size
	wxRect clientSize = GetClientSize();

	int nWidth = clientSize.GetWidth();
	int nHeight = clientSize.GetHeight();

	// calculate max size
	wxSize virtualSize = CalculateVirtualSize();
 	if (nWidth < virtualSize.GetWidth()) nWidth = virtualSize.GetWidth();
 	if (nHeight < virtualSize.GetHeight()) nHeight = virtualSize.GetHeight();

	// fill background
	m_dcBackBuffer.SetBrush(*wxLIGHT_GREY_BRUSH);
	m_dcBackBuffer.SetPen(*wxTRANSPARENT_PEN);
	m_dcBackBuffer.DrawRectangle(0, 0, nWidth*m_nZoom, nHeight*m_nZoom);

	// draw cross
	wxBrush brushGrid;
	brushGrid.SetColour(*wxWHITE);
	brushGrid.SetStyle(wxBRUSHSTYLE_CROSSDIAG_HATCH);
	m_dcBackBuffer.SetBrush(brushGrid);
	m_dcBackBuffer.SetPen(*wxTRANSPARENT_PEN);
	m_dcBackBuffer.DrawRectangle(0, 0, nWidth*m_nZoom, nHeight*m_nZoom);

	// TODO: custom draw
// 	if (pbmpImage)
// 	{
// 		m_dcBackBuffer.StretchBlit(-m_ptOrigin, pbmpImage->GetSize()*m_nZoom, &m_dcImage, wxPoint(0, 0), pbmpImage->GetSize());
// 		DrawSelection(m_dcBackBuffer);
// 	}

	// flush to dc
	dc.Blit(0, 0, m_bmpBackBuffer.GetWidth(), m_bmpBackBuffer.GetHeight(), &m_dcBackBuffer, 0, 0);
}

void BaseEditor::OnMouseWheel(wxMouseEvent& event)
{
	int lines = -event.GetWheelRotation() / event.GetWheelDelta();

	if (event.ShiftDown())
	{
		int nPos = GetScrollPos(wxHORIZONTAL);
		SetScrollPos(wxHORIZONTAL, nPos + lines * event.GetLinesPerAction() * SCROLL_LINE_DISTANCE);
		UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	}
	else if (event.ControlDown())
	{
		if (lines < 0)
		{
			ZoomIn();
		}
		else
		{
			ZoomOut();
		}
	}
	else
	{
		int nPos = GetScrollPos(wxVERTICAL);
		SetScrollPos(wxVERTICAL, nPos + lines * event.GetLinesPerAction() * SCROLL_LINE_DISTANCE);
		UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	}
}

void BaseEditor::OnMouseLButtonDown(wxMouseEvent& event)
{
	SetFocus();
	// TODO: notify l button down
}

void BaseEditor::OnSize(wxSizeEvent& event)
{
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));

	if (m_bmpBackBuffer.GetSize() != GetClientSize())
	{
		m_dcBackBuffer.SelectObject(wxNullBitmap);
		m_bmpBackBuffer.Create(GetClientSize());
		m_dcBackBuffer.SelectObject(m_bmpBackBuffer);
	}

	event.Skip();
}

void BaseEditor::OnScrollLineUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void BaseEditor::OnScrollLineDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void BaseEditor::OnScrollPageUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void BaseEditor::OnScrollPageDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void BaseEditor::OnScrollThumbTrack(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nPos = event.GetPosition();
	if (nOrientation == wxHORIZONTAL)
	{
		UpdateScrollPosition(nPos, GetScrollPos(wxVERTICAL));
	}
	else
	{
		UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), nPos);
	}
}

void BaseEditor::OnScrollThumbRelease(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nPos = event.GetPosition();
	SetScrollPos(nOrientation, nPos, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void BaseEditor::UpdateVirtualSize()
{
	m_sizeVirtual = CalculateVirtualSize();
	m_sizeVirtual *= m_nZoom;

	wxRect rect = GetClientRect();

	// hide unnessary scroll bar
	bool bShowHorizontal = true;
	if (m_sizeVirtual.GetWidth() <= rect.GetWidth())
	{
		SetScrollbar(wxHORIZONTAL, 0, 0, 0, true);
		bShowHorizontal = false;
	}

	bool bShowVertical = true;
	if (m_sizeVirtual.GetHeight() <= rect.GetHeight())
	{
		SetScrollbar(wxVERTICAL, 0, 0, 0, true);
		bShowVertical = false;
	}

	// get the rect again, it may be difference from the old rect after hide the scroll bar
	rect = GetClientRect();

	// recalculate the scroll bar range
	if (bShowHorizontal)
	{
		SetScrollbar(wxHORIZONTAL, m_ptOrigin.x, rect.GetWidth(), m_sizeVirtual.GetWidth(), true);
	}
	if (bShowVertical)
	{
		SetScrollbar(wxVERTICAL, m_ptOrigin.y, rect.GetHeight(), m_sizeVirtual.GetHeight(), true);
	}
}

const wxSize& BaseEditor::GetVirtualSize()
{
	return m_sizeVirtual;
}

void BaseEditor::UpdateScrollPosition(int x, int y)
{
	m_ptOrigin.x = x;
	m_ptOrigin.y = y;

	Refresh(false);
}

wxSize BaseEditor::CalculateVirtualSize()
{
	return wxSize(0, 0);
}
