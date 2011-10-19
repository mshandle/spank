/*!
 * \file UIImagePieceView.cpp
 * \date 01-09-2011 21:21:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIImagePieceView.h"
#include <wx/dcclient.h>
#include "wxImagePieceEvent.h"
#include "CombinaPiece.h"

BEGIN_EVENT_TABLE(UIImagePieceView, wxWindow)
	EVT_PAINT(UIImagePieceView::OnPaint)
	EVT_MOUSEWHEEL(UIImagePieceView::OnMouseWheel)
	EVT_MOTION(UIImagePieceView::OnMouseMove)
	EVT_LEFT_DOWN(UIImagePieceView::OnMouseLButtonDown)
	EVT_LEFT_UP(UIImagePieceView::OnMouseLButtonUp)
	EVT_SIZE(UIImagePieceView::OnSize)
	EVT_SCROLLWIN_LINEUP(UIImagePieceView::OnScrollLineUp)
	EVT_SCROLLWIN_LINEDOWN(UIImagePieceView::OnScrollLineDown)
	EVT_SCROLLWIN_PAGEUP(UIImagePieceView::OnScrollPageUp)
	EVT_SCROLLWIN_PAGEDOWN(UIImagePieceView::OnScrollPageDown)
	EVT_SCROLLWIN_THUMBTRACK(UIImagePieceView::OnScrollThumbTrack)
	EVT_SCROLLWIN_THUMBRELEASE(UIImagePieceView::OnScrollThumbRelease)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(UIImagePieceView, wxWindow)

UIImagePieceView::UIImagePieceView()
{
	Init();
}

UIImagePieceView::UIImagePieceView(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
{
	Init();
	Create(parent, winid, pos, size, style, name);
}

UIImagePieceView::~UIImagePieceView()
{
	Release();
}

void UIImagePieceView::Init()
{
	// load grid brush
	m_bmpGrid.LoadFile(wxT("images/grid.png"), wxBITMAP_TYPE_PNG);
	m_brushGrid.SetStyle(wxBRUSHSTYLE_STIPPLE);
	m_brushGrid.SetStipple(m_bmpGrid);
	
	m_nZoom = ZOOM_MIN;

	// load cursor
	m_eCurType = CT_DEFAULT;
	m_pCursors[CT_DEFAULT] = new wxCursor(wxT("images/size3_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_HORIZONTAL] = new wxCursor(wxT("images/size3_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_VERTICAL] = new wxCursor(wxT("images/size4_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_DIAGONAL] = new wxCursor(wxT("images/size2_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_DIAGONAL_INV] = new wxCursor(wxT("images/size1_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_MOVE] = new wxCursor(wxT("images/move_r.cur"), wxBITMAP_TYPE_CUR);

	m_CurrDragMode = PIC_UNKNOWN;

	m_sizeVirtual.Set(DEFAULT_VIRTUAL_SIZE*m_nZoom, DEFAULT_VIRTUAL_SIZE*m_nZoom);
	m_ptOrigin.x = 0;
	m_ptOrigin.y = 0;

	m_strImage = wxEmptyString;
	m_pPieceInfo = NULL;
	m_pbmpImage = &m_bmpGrid;
}

void UIImagePieceView::Release()
{
	for (int i = 0; i < NUM_CT; ++i)
	{
		delete m_pCursors[i];
		m_pCursors[i] = NULL;
	}
	for(TM_BITMAP_CACHE::iterator it = m_vBitmap.begin(); it != m_vBitmap.end();)
	{
		wxBitmap* pBitMap = it->second;
		delete pBitMap;
		pBitMap= NULL;
		it = m_vBitmap.erase(it);
	}
	for(TM_PIECE::iterator it = m_vPiece.begin(); it != m_vPiece.end(); ++it)
	{
		it->second.Release();
	}
}

bool UIImagePieceView::Create(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
{
	if (!wxWindow::Create(parent, winid, pos, size, style, name)) return false;

	return true;
}

wxSize UIImagePieceView::DoGetBestSize() const
{
	return m_sizeVirtual;
}

void UIImagePieceView::Update()
{
	Refresh(false);
}

void UIImagePieceView::SaveImage()
{
	CombinaPiece::Combina(m_vPiece, m_vBitmap);
}
bool UIImagePieceView::LoadImageFromFile(const wxString& strImage)
{
	m_strImage = strImage;
	TM_BITMAP_CACHE::iterator it = m_vBitmap.find(strImage);
	if( it == m_vBitmap.end())
	{
		m_pbmpImage = new wxBitmap();
		if (!m_pbmpImage->LoadFile(m_strImage, wxBITMAP_TYPE_PNG)) return false;
		m_vBitmap.insert(std::make_pair(strImage, m_pbmpImage));
	}
	else
	{
		m_pbmpImage = it->second;
	}
	m_dcImage.SelectObject(*m_pbmpImage);

	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	return true;
}

const wxString UIImagePieceView::GetBackFileName() const
{
	return m_strImage;
}
void UIImagePieceView::SetSelectedPiece(const UIImagePieceDocument::PIECE_INFO* pPieceInfo)
{
	m_eType = NORMAL_PIECE_INFO;
	m_pPieceInfo = pPieceInfo;

	m_rectSelected = m_pPieceInfo->rect;
	Refresh(false);
}

void UIImagePieceView::SetSelectedPiece(const wxString StrImportView)
{
	m_eType = IMPORT_PIECE_INFO;
	TM_PIECE::iterator pieceInof  = m_vPiece.find(StrImportView);
	if(pieceInof != m_vPiece.end())
	{
		m_StrImportView = StrImportView;
		m_rectSelected = (*pieceInof).second.rect;
		Refresh(false);
	}

}
const UIImagePieceDocument::PIECE_INFO* UIImagePieceView::GetSelectedPiece() const
{
	return m_pPieceInfo;
}

bool UIImagePieceView::ZoomIn()
{
	return Zoom(m_nZoom+1);
}

bool UIImagePieceView::ZoomOut()
{
	return Zoom(m_nZoom-1);
}

bool UIImagePieceView::Zoom(int zoom)
{
	if (zoom < ZOOM_MIN || zoom > ZOOM_MAX) return false;
	if (m_nZoom == zoom) return true;

	m_ptOrigin = (m_ptOrigin/m_nZoom)*zoom;
	m_nZoom = zoom;
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));

	return true;
}

int UIImagePieceView::GetZoom() const
{
	return m_nZoom;
}

bool UIImagePieceView::MoveRelative(int x, int y)
{
	if(m_eType == NORMAL_PIECE_INFO)
	{
		if (!m_pPieceInfo) return false;
		m_rectSelected.x += x;
		m_rectSelected.y += y;
	}
	else if( m_eType == IMPORT_PIECE_INFO )
	{
		m_rectSelected.x += x;
		m_rectSelected.y += y;
		TM_PIECE::iterator it = m_vPiece.find(m_StrImportView);
		(*it).second.rect = m_rectSelected;
	}
	Refresh(false);
	return true;
}

void UIImagePieceView::AddImportPiece(PIECEVIEW_INFO ImpotPiece)
{
	m_vPiece.insert(std::make_pair(ImpotPiece.StrImage, ImpotPiece));
}

void UIImagePieceView::UpdateBitMapCache()
{
	TM_BITMAP_CACHE::iterator it = m_vBitmap.find(m_strImage);
	m_dcImage.SelectObject(*(it->second));
}
UIImagePieceView::TM_PIECE& UIImagePieceView::GetPieceMap()
{
	return m_vPiece;
}	

UIImagePieceView::TM_BITMAP_CACHE& UIImagePieceView::GetBitCacheMap()
{
	return m_vBitmap;
}
void UIImagePieceView::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	// get client size
	wxRect clientSize = GetClientSize();

	// draw image
	int nWidth = clientSize.GetWidth() > m_pbmpImage->GetWidth() ? clientSize.GetWidth() : m_pbmpImage->GetWidth();
	int nHeight = clientSize.GetHeight() > m_pbmpImage->GetHeight() ? clientSize.GetHeight() : m_pbmpImage->GetHeight();

	m_dcBackBuffer.SetBrush(m_brushGrid);
	m_dcBackBuffer.SetPen(*wxTRANSPARENT_PEN);
	m_dcBackBuffer.DrawRectangle(0, 0, nWidth*m_nZoom, nHeight*m_nZoom);
	//Draw the import piece in the Image;
	m_dcBackBuffer.StretchBlit(-m_ptOrigin, m_pbmpImage->GetSize()*m_nZoom, &m_dcImage, wxPoint(0, 0), m_pbmpImage->GetSize());

	DrawPieces(m_dcImage);

	if (m_pPieceInfo)
	{
		DrawRect(m_dcBackBuffer, m_rectSelected);
	}
	
	// flush to dc
	dc.Blit(0, 0, m_bmpBackBuffer.GetWidth(), m_bmpBackBuffer.GetHeight(), &m_dcBackBuffer, 0, 0);

}

void UIImagePieceView::OnMouseWheel(wxMouseEvent& event)
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
		if (lines < 0) ZoomIn();
		else ZoomOut();
	}
	else
	{
		int nPos = GetScrollPos(wxVERTICAL);
		SetScrollPos(wxVERTICAL, nPos + lines * event.GetLinesPerAction() * SCROLL_LINE_DISTANCE);
		UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	}
	event.Skip();
}

void UIImagePieceView::OnMouseMove(wxMouseEvent& event)
{
 	wxPoint ptMouseMove = event.GetPosition() + m_ptOrigin;
 
 	if (m_CurrDragMode == PIC_UNKNOWN && m_pPieceInfo != NULL)
 	{
 		wxRect zoomedRect(m_rectSelected.x*m_nZoom, m_rectSelected.y*m_nZoom, m_rectSelected.width*m_nZoom, m_rectSelected.height*m_nZoom);
 
 		POINT_IN_CONNER eType = CheckPointInConner(zoomedRect, ptMouseMove);
 		switch (eType)
 		{
 		case PIC_TOP_LEFT:
 		case PIC_BOTTOM_RIGHT:
 			{
 				SetCursorByType(CT_DIAGONAL);
 			}
 			break;
 		case PIC_TOP_RIGHT:
 		case PIC_BOTTOM_LEFT:
 			{
 				SetCursorByType(CT_DIAGONAL_INV);
 			}
 			break;
 		case PIC_TOP_CENTER:
 		case PIC_BOTTOM_CENTER:
 			{
 				SetCursorByType(CT_VERTICAL);
 			}
 			break;
 		case PIC_MIDDLE_LEFT:
 		case PIC_MIDDLE_RIGHT:
 			{
 				SetCursorByType(CT_HORIZONTAL);
 			}
 			break;
 		case PIC_MIDDLE_CENTER:
 			{
 				SetCursorByType(CT_MOVE);
 			}
 			break;
 		default:
 			{
 				SetCursorByType(CT_DEFAULT);
 			}
 			break;
 		}
 	}
 	else if (m_CurrDragMode != PIC_UNKNOWN && m_eType == NORMAL_PIECE_INFO)
 	{
		
		switch (m_CurrDragMode)
		{
		case PIC_TOP_LEFT:
			{
				m_rectSelected.x = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.x;
				m_rectSelected.y = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.y;
				m_rectSelected.width = -(ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.width;
				m_rectSelected.height = -(ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.height;
			}
			break;
		case PIC_BOTTOM_RIGHT:
			{
				m_rectSelected.width = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.width;
				m_rectSelected.height = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.height;
			}
			break;
		case PIC_TOP_RIGHT:
			{
				m_rectSelected.y = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.y;
				m_rectSelected.width = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.width;
				m_rectSelected.height = -(ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.height;
			}
			break;
		case PIC_BOTTOM_LEFT:
			{
				m_rectSelected.x = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.x;
				m_rectSelected.width = -(ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.width;
				m_rectSelected.height = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.height;
			}
			break;
		case PIC_TOP_CENTER:
			{
				m_rectSelected.y = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.y;
				m_rectSelected.height = -(ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.height;
			}
			break;
		case PIC_BOTTOM_CENTER:
			{
				m_rectSelected.height = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.height;
			}
			break;
		case PIC_MIDDLE_LEFT:
			{
				m_rectSelected.x = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.x;
				m_rectSelected.width = -(ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.width;
			}
			break;
		case PIC_MIDDLE_RIGHT:
			{
				m_rectSelected.width = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.width;
			}
			break;
		case PIC_MIDDLE_CENTER:
			{
				m_rectSelected.x = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.x;
				m_rectSelected.y = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.y;
			}
			break;
		}
 		// apply drag rect
 		Refresh(false);
 	}
	else if(m_CurrDragMode == PIC_MIDDLE_CENTER && m_eType == IMPORT_PIECE_INFO)
	{
		//TODO: Change the Import view the position
		m_rectSelected.x = (ptMouseMove.x - m_ptMouseDown.x)/m_nZoom + m_rectSelectedBackup.x;
		m_rectSelected.y = (ptMouseMove.y - m_ptMouseDown.y)/m_nZoom + m_rectSelectedBackup.y;
		TM_PIECE::iterator it = m_vPiece.find(m_StrImportView);
		(*it).second.rect = m_rectSelected;
		Update();
	}
	event.Skip();
}

void UIImagePieceView::OnMouseLButtonDown(wxMouseEvent& event)
{
	if(m_eType == NORMAL_PIECE_INFO && m_pPieceInfo)
	{
		m_ptMouseDown = event.GetPosition() + m_ptOrigin;

		wxRect zoomedRect = wxRect(m_rectSelected.x*m_nZoom, m_rectSelected.y*m_nZoom, m_rectSelected.width*m_nZoom, m_rectSelected.height*m_nZoom);

		m_CurrDragMode = CheckPointInConner(zoomedRect, m_ptMouseDown);
		if (m_CurrDragMode != PIC_UNKNOWN)
		{
			CaptureMouse();
		}

		m_rectSelectedBackup = m_rectSelected;
		
	}
	else if( m_eType == IMPORT_PIECE_INFO && !m_StrImportView.IsEmpty())
	{
		m_ptMouseDown = event.GetPosition() + m_ptOrigin;

		wxRect zoomedRect = wxRect(m_rectSelected.x*m_nZoom, m_rectSelected.y*m_nZoom, m_rectSelected.width*m_nZoom, m_rectSelected.height*m_nZoom);

		m_CurrDragMode = CheckPointInConner(zoomedRect, m_ptMouseDown);
		if (m_CurrDragMode != PIC_UNKNOWN)
		{
			CaptureMouse();
		}
		
		m_rectSelectedBackup = m_rectSelected;
	}


	event.Skip();
}

void UIImagePieceView::OnMouseLButtonUp(wxMouseEvent& event)
{
 	if (m_CurrDragMode != PIC_UNKNOWN && m_pPieceInfo != NULL && m_eType == NORMAL_PIECE_INFO)
 	{
 		// apply drag
 		m_CurrDragMode = PIC_UNKNOWN;

		ReleaseMouse();

		if (m_rectSelected.width < 0)
		{
			m_rectSelected.width = -m_rectSelected.width;
			m_rectSelected.x -= m_rectSelected.width;
		}

		if (m_rectSelected.height < 0)
		{
			m_rectSelected.height = -m_rectSelected.height;
			m_rectSelected.y -= m_rectSelected.height;
		}

		Refresh(false);

		wxImagePieceEvent evtPiece(wxEVT_COMMAND_IMAGE_PIECE_CHANGED, GetId());
		evtPiece.SetEventObject(this);

		UIImagePieceDocument::PIECE_INFO pieceInfo = (*m_pPieceInfo);
		pieceInfo.rect = m_rectSelected;
		evtPiece.SetPieceInfo(pieceInfo);
		GetEventHandler()->ProcessEvent(evtPiece);
 	}
	else if(m_eType == IMPORT_PIECE_INFO && !m_StrImportView.IsEmpty() && m_CurrDragMode != PIC_UNKNOWN)
	{
		//TODO: Save the New Position;
		m_CurrDragMode = PIC_UNKNOWN;
		ReleaseMouse();
		if (m_rectSelected.width < 0)
		{
			m_rectSelected.width = -m_rectSelected.width;
			m_rectSelected.x -= m_rectSelected.width;
		}

		if (m_rectSelected.height < 0)
		{
			m_rectSelected.height = -m_rectSelected.height;
			m_rectSelected.y -= m_rectSelected.height;
		}

		Refresh(false);
		TM_PIECE::iterator it = m_vPiece.find(m_StrImportView);
		(*it).second.rect = m_rectSelected;
	}

	event.Skip();
}

void UIImagePieceView::OnSize(wxSizeEvent& event)
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

void UIImagePieceView::OnScrollLineUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImagePieceView::OnScrollLineDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImagePieceView::OnScrollPageUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImagePieceView::OnScrollPageDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImagePieceView::OnScrollThumbTrack(wxScrollWinEvent& event)
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

void UIImagePieceView::OnScrollThumbRelease(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nPos = event.GetPosition();
	SetScrollPos(nOrientation, nPos, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImagePieceView::UpdateVirtualSize()
{
	m_sizeVirtual = m_pbmpImage->GetSize();
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

const wxSize& UIImagePieceView::GetVirtualSize()
{
	return m_sizeVirtual;
}

void UIImagePieceView::UpdateScrollPosition(int x, int y)
{
	m_ptOrigin.x = x;
	m_ptOrigin.y = y;

	Refresh(false);
}

void UIImagePieceView::DrawRect(wxDC& dc, const wxRect& rect)
{
 	dc.SetPen(*wxBLUE_PEN);
 	dc.SetBrush(*wxTRANSPARENT_BRUSH);

 	wxRect zoomedRect(rect.x*m_nZoom-m_ptOrigin.x, rect.y*m_nZoom-m_ptOrigin.y, rect.width*m_nZoom, rect.height*m_nZoom);
 	dc.DrawRectangle(zoomedRect);
 
 	dc.SetBrush(*wxBLUE_BRUSH);
 	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width/2-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
 	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height/2-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height/2-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
 	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width/2-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
}
void UIImagePieceView::DrawPieces(wxDC& dc)
{
	for(TM_PIECE::iterator it = m_vPiece.begin(); it !=  m_vPiece.end(); ++it)
	{
		if(m_strImage == (*it).second.StrBackGroundImage)
		{
			wxSize Size =  (*it).second.pMemDC->GetSize();
			wxDC* pSource = (*it).second.pMemDC;
			int x = (*it).second.rect.x * m_nZoom;
			int y = (*it).second.rect.y * m_nZoom;
			x -= m_ptOrigin.x;
			y -= m_ptOrigin.y;	
			m_dcBackBuffer.StretchBlit(wxPoint(x, y), Size * m_nZoom, pSource, wxPoint(0,0), Size);
		}
			
	}
}
UIImagePieceView::POINT_IN_CONNER UIImagePieceView::CheckPointInConner(const wxRect& rect, const wxPoint& pt)
{
	wxRect rectTopLeft(rect.x-RECT_SENSOR_SIZE, rect.y-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectTopLeft.Contains(pt)) return PIC_TOP_LEFT;

	wxRect rectTopCenter(rect.x+rect.width/2-RECT_SENSOR_SIZE, rect.y-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectTopCenter.Contains(pt)) return PIC_TOP_CENTER;

	wxRect rectTopRight(rect.x+rect.width-RECT_SENSOR_SIZE, rect.y-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectTopRight.Contains(pt)) return PIC_TOP_RIGHT;

	wxRect rectMiddleLeft(rect.x-RECT_SENSOR_SIZE, rect.y+rect.height/2-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectMiddleLeft.Contains(pt)) return PIC_MIDDLE_LEFT;

	wxRect rectMiddleRight(rect.x+rect.width-RECT_SENSOR_SIZE, rect.y+rect.height/2-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectMiddleRight.Contains(pt)) return PIC_MIDDLE_RIGHT;

	wxRect rectBottomLeft(rect.x-RECT_SENSOR_SIZE, rect.y+rect.height-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectBottomLeft.Contains(pt)) return PIC_BOTTOM_LEFT;

	wxRect rectBottomCenter(rect.x+rect.width/2-RECT_SENSOR_SIZE, rect.y+rect.height-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectBottomCenter.Contains(pt)) return PIC_BOTTOM_CENTER;

	wxRect rectBottomRight(rect.x+rect.width-RECT_SENSOR_SIZE, rect.y+rect.height-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectBottomRight.Contains(pt)) return PIC_BOTTOM_RIGHT;

	if (rect.Contains(pt)) return PIC_MIDDLE_CENTER;

	return PIC_UNKNOWN;
}

void UIImagePieceView::SetCursorByType(CURSOR_TYPE eType)
{
	if (m_eCurType == eType) return;
	m_eCurType = eType;

	if (m_eCurType == CT_DEFAULT)
	{
		SetCursor(wxNullCursor);
	}
	else
	{
		SetCursor(*m_pCursors[eType]);
	}
}

void UIImagePieceView::ClearImportPiece()
{
	for(TM_PIECE::iterator it = m_vPiece.begin(); it != m_vPiece.end();)
	{
		(*it).second.Release();
		it = m_vPiece.erase(it);
	}
}
