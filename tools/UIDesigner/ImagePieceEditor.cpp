/*!
 * \file ImagePieceEditor.cpp
 * \date 2-14-2012 1:24:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImagePieceEditor.h"
#include "document/ImagePieceDocument.h"
#include "transformer/PieceListTransformer.h"
#include "transformer/ImageListTransformer.h"

#include <wx/dcclient.h>

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

BEGIN_EVENT_TABLE(ImagePieceEditor, wxWindow)
	EVT_PAINT(ImagePieceEditor::OnPaint)
	EVT_MOUSEWHEEL(ImagePieceEditor::OnMouseWheel)
	EVT_LEFT_DOWN(ImagePieceEditor::OnMouseLButtonDown)
	EVT_SIZE(ImagePieceEditor::OnSize)
	EVT_SCROLLWIN_LINEUP(ImagePieceEditor::OnScrollLineUp)
	EVT_SCROLLWIN_LINEDOWN(ImagePieceEditor::OnScrollLineDown)
	EVT_SCROLLWIN_PAGEUP(ImagePieceEditor::OnScrollPageUp)
	EVT_SCROLLWIN_PAGEDOWN(ImagePieceEditor::OnScrollPageDown)
	EVT_SCROLLWIN_THUMBTRACK(ImagePieceEditor::OnScrollThumbTrack)
	EVT_SCROLLWIN_THUMBRELEASE(ImagePieceEditor::OnScrollThumbRelease)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(ImagePieceEditor, wxWindow)

ImagePieceEditor* ImagePieceEditor::m_pImagePieceEditor = NULL;

ImagePieceEditor::ImagePieceEditor()
{
	Init();
}

ImagePieceEditor::ImagePieceEditor(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
{
	Init();
	Create(parent, winid, pos, size, style, name);
}

ImagePieceEditor::~ImagePieceEditor()
{
	Release();
}

void ImagePieceEditor::Init()
{
	m_pImagePieceEditor = this;

	m_nZoom = ZOOM_MIN;

	m_sizeVirtual.Set(DEFAULT_VIRTUAL_SIZE*m_nZoom, DEFAULT_VIRTUAL_SIZE*m_nZoom);
	m_ptOrigin.x = 0;
	m_ptOrigin.y = 0;

	m_pPieceInfo = NULL;
	m_pImageInfo = NULL;
}

void ImagePieceEditor::Release()
{
	m_pImagePieceEditor = NULL;
}

bool ImagePieceEditor::Create(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
{
	if (!wxWindow::Create(parent, winid, pos, size, style, name)) return false;

	return true;
}

wxSize ImagePieceEditor::DoGetBestSize() const
{
	return m_sizeVirtual;
}

ImagePieceEditor& ImagePieceEditor::GetInstance()
{
	return *m_pImagePieceEditor;
}

void ImagePieceEditor::SetSelection(PieceInfo* pPieceInfo)
{
	m_pPieceInfo = pPieceInfo;
	Refresh(false);
}

PieceInfo* ImagePieceEditor::GetSelection() const
{
	return m_pPieceInfo;
}

bool ImagePieceEditor::ZoomIn()
{
	return Zoom(m_nZoom+1);
}

bool ImagePieceEditor::ZoomOut()
{
	return Zoom(m_nZoom-1);
}

bool ImagePieceEditor::Zoom(int zoom)
{
	if (zoom < ZOOM_MIN || zoom > ZOOM_MAX) return false;
	if (m_nZoom == zoom) return true;

	m_ptOrigin = (m_ptOrigin/m_nZoom)*zoom;
	m_nZoom = zoom;
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));

	return true;
}

int ImagePieceEditor::GetZoom() const
{
	return m_nZoom;
}

void ImagePieceEditor::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	// get client size
	wxRect clientSize = GetClientSize();

	int nWidth = clientSize.GetWidth();
	int nHeight = clientSize.GetHeight();

	wxBitmap* pbmpImage = NULL;
	if (m_pImageInfo) pbmpImage = m_pImageInfo->GetImage();
	if (pbmpImage && nWidth < pbmpImage->GetWidth()) nWidth = pbmpImage->GetWidth();
	if (pbmpImage && nHeight < pbmpImage->GetHeight()) nHeight = pbmpImage->GetHeight();

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

	// draw image
	if (pbmpImage)
	{
		m_dcBackBuffer.StretchBlit(-m_ptOrigin, pbmpImage->GetSize()*m_nZoom, &m_dcImage, wxPoint(0, 0), pbmpImage->GetSize());
		DrawSelection(m_dcBackBuffer);
	}
	
	// flush to dc
	dc.Blit(0, 0, m_bmpBackBuffer.GetWidth(), m_bmpBackBuffer.GetHeight(), &m_dcBackBuffer, 0, 0);
}

void ImagePieceEditor::OnMouseWheel(wxMouseEvent& event)
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

void ImagePieceEditor::OnMouseLButtonDown(wxMouseEvent& event)
{
	SetFocus();

	wxPoint posMouse = (event.GetPosition() + m_ptOrigin) / m_nZoom;
	PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfoUnderPoint(posMouse, m_pImageInfo);
	SetSelection(pPieceInfo);
	PieceListTransformer::GetInstance().SetSelectedItem(pPieceInfo);
}

void ImagePieceEditor::OnSize(wxSizeEvent& event)
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

void ImagePieceEditor::OnScrollLineUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void ImagePieceEditor::OnScrollLineDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void ImagePieceEditor::OnScrollPageUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void ImagePieceEditor::OnScrollPageDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void ImagePieceEditor::OnScrollThumbTrack(wxScrollWinEvent& event)
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

void ImagePieceEditor::OnScrollThumbRelease(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nPos = event.GetPosition();
	SetScrollPos(nOrientation, nPos, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void ImagePieceEditor::UpdateVirtualSize()
{
	if (!m_pImageInfo) return;

	wxBitmap* pbmpImage = m_pImageInfo->GetImage();
	if (!pbmpImage) return;

	m_sizeVirtual = pbmpImage->GetSize();
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

const wxSize& ImagePieceEditor::GetVirtualSize()
{
	return m_sizeVirtual;
}

void ImagePieceEditor::UpdateScrollPosition(int x, int y)
{
	m_ptOrigin.x = x;
	m_ptOrigin.y = y;

	Refresh(false);
}

void ImagePieceEditor::DrawSelection(wxDC& dc)
{
	if (!m_pPieceInfo) return;

 	dc.SetPen(*wxRED_PEN);
 	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	const wxRect& rect = m_pPieceInfo->GetRect();
 	wxRect zoomedRect(rect.x*m_nZoom-m_ptOrigin.x, rect.y*m_nZoom-m_ptOrigin.y, rect.width*m_nZoom, rect.height*m_nZoom);
 	dc.DrawRectangle(zoomedRect);
}

bool ImagePieceEditor::SetImage(ImageInfo* pImageInfo)
{
	if (m_pImageInfo == pImageInfo) return false;
	m_pImageInfo = pImageInfo;

	if (m_pImageInfo && m_pImageInfo->GetImage() != NULL)
	{
		m_dcImage.SelectObject(*m_pImageInfo->GetImage());
	}
	else
	{
		m_dcImage.SelectObject(wxNullBitmap);
	}

	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	return true;
}

ImageInfo* ImagePieceEditor::GetImage() const
{
	return m_pImageInfo;
}
