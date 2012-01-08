/*!
 * \file UIImagePieceEditor.h
 * \date 01-09-2011 21:21:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIIMAGEPIECEEDITOR_H__
#define __UIIMAGEPIECEEDITOR_H__

#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>
#include "UIImagePieceDocument.h"
#include <vector>
#include <map>

class UIImagePieceEditor : public wxWindow
{
	DECLARE_DYNAMIC_CLASS(UIImagePieceEditor)
	DECLARE_EVENT_TABLE()

public:
	enum CONST_DEFINE
	{
		SCROLL_LINE_DISTANCE = 10,
		ZOOM_MIN = 1,
		ZOOM_STEP = 1,
		ZOOM_MAX = 10,
		RECT_SPOT_SIZE = 2,
		RECT_SENSOR_SIZE = 4,
		DEFAULT_VIRTUAL_SIZE = 100,
	};

	enum SELECT_PIECE_TYPE
	{
		NORMAL_PIECE_INFO = 0,
		IMPORT_PIECE_INFO,
	};

	enum POINT_IN_CONNER
	{
		PIC_UNKNOWN = 0,
		PIC_TOP_LEFT,
		PIC_TOP_CENTER,
		PIC_TOP_RIGHT,
		PIC_MIDDLE_LEFT,
		PIC_MIDDLE_CENTER,
		PIC_MIDDLE_RIGHT,
		PIC_BOTTOM_LEFT,
		PIC_BOTTOM_CENTER,
		PIC_BOTTOM_RIGHT,
	};

	enum CURSOR_TYPE
	{
		CT_DEFAULT = 0,
		CT_HORIZONTAL,
		CT_VERTICAL,
		CT_DIAGONAL,
		CT_DIAGONAL_INV,
		CT_MOVE,
		NUM_CT,
	};

	typedef struct PIECE_VIEW_INFO_tag
	{
		wxString strBgImage;
		wxString strImage;
		wxBitmap* pBitmap;
		wxMemoryDC* pMemDc;
		wxRect pieceRect;
	} PIECE_VIEW_INFO;

	typedef std::map<wxString, PIECE_VIEW_INFO> TM_PIECE_VIEW_INFO;
	typedef std::map<wxString, wxBitmap*> TM_BITMAP_CACHE;

public:
	UIImagePieceEditor();
	UIImagePieceEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual ~UIImagePieceEditor();

	bool Create(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual wxSize DoGetBestSize() const;
	void SaveImage();
	bool LoadImageFromFile(const wxString& strImage);
	void UpdateBitMapCache();

	void SetSelectedPiece(const UIImagePieceDocument::PIECE_INFO* pPieceInfo);
	void SetSelectedPiece(const wxString& strPieceId);

	const UIImagePieceDocument::PIECE_INFO* GetSelectedPiece() const;

	TM_BITMAP_CACHE& GetBitCacheMap();

	bool ZoomIn();
	bool ZoomOut();
	bool Zoom(int zoom);
	int GetZoom() const;

	bool MoveRelative(int x, int y);

	const TM_PIECE_VIEW_INFO& GetImportedPieceMap();
	bool AddImportedPiece(const PIECE_VIEW_INFO& pieceInfo);
	const PIECE_VIEW_INFO* FindImportedPiece(const wxString& strPieceId);
	void ClearImportedPiece();

	bool AddBitmapCache(const wxString& strImageId, wxBitmap* pBitmap);
	wxBitmap* FindBitmapCache(const wxString& strImageId);
	void ClearBitmapCache();

private:
	void Init();
	void Release();

	void OnPaint(wxPaintEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLButtonDown(wxMouseEvent& event);
	void OnMouseLButtonUp(wxMouseEvent& event);
	void OnSize(wxSizeEvent& event);

	void OnScrollLineUp(wxScrollWinEvent& event);
	void OnScrollLineDown(wxScrollWinEvent& event);
	void OnScrollPageUp(wxScrollWinEvent& event);
	void OnScrollPageDown(wxScrollWinEvent& event);
	void OnScrollThumbTrack(wxScrollWinEvent& event);
	void OnScrollThumbRelease(wxScrollWinEvent& event);

	void UpdateVirtualSize();
	const wxSize& GetVirtualSize();
	void UpdateScrollPosition(int x, int y);

	void DrawPieces(wxDC& dc);
	void DrawRect(wxDC& dc, const wxRect& rect);
	POINT_IN_CONNER CheckPointInConner(const wxRect& rect, const wxPoint& pt);
	void SetCursorByType(CURSOR_TYPE eType);

private:
	wxBitmap* m_pbmpImage;
	wxMemoryDC m_dcImage;
	
	wxBitmap m_bmpBackBuffer;
	wxMemoryDC m_dcBackBuffer;

	wxBitmap m_bmpGrid;
	wxBrush m_brushGrid;
	
	int m_nZoom;

	wxRect m_rectSelected;
	wxRect m_rectSelectedBackup;
	
	wxCursor* m_pCursors[NUM_CT];
	CURSOR_TYPE m_eCurType;

	POINT_IN_CONNER m_CurrDragMode;
	wxPoint m_ptMouseDown;

	wxSize m_sizeVirtual;
	wxPoint m_ptOrigin;

	wxString m_strImage;
	const UIImagePieceDocument::PIECE_INFO* m_pPieceInfo;
	wxString m_strImportView;
	SELECT_PIECE_TYPE m_eType;

	TM_PIECE_VIEW_INFO m_vImportedPiece;
	TM_BITMAP_CACHE m_vBitmapCache;

};
#endif // __UIIMAGEPIECEEDITOR_H__
