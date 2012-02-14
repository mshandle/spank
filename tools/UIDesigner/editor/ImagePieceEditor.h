/*!
 * \file ImagePieceEditor.h
 * \date 2-14-2012 1:24:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGEPIECEEDITOR_H__
#define __IMAGEPIECEEDITOR_H__

#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>
#include <vector>
#include <map>

#include "../document/PieceInfo.h"
#include "../document/ImageInfo.h"

class ImagePieceEditor : public wxWindow
{
	DECLARE_DYNAMIC_CLASS(ImagePieceEditor)
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
	ImagePieceEditor();
	ImagePieceEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual ~ImagePieceEditor();

	bool Create(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual wxSize DoGetBestSize() const;

	static ImagePieceEditor& GetInstance();

	void SetSelection(PieceInfo* pPieceInfo);
	PieceInfo* GetSelection() const;

	bool SetImage(ImageInfo* pImageInfo);
	ImageInfo* GetImage() const;

	bool ZoomIn();
	bool ZoomOut();
	bool Zoom(int zoom);
	int GetZoom() const;

private:
	void Init();
	void Release();

	void OnPaint(wxPaintEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnMouseLButtonDown(wxMouseEvent& event);
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

	void DrawSelection(wxDC& dc);

private:
	static ImagePieceEditor* m_pImagePieceEditor;
	wxMemoryDC m_dcImage;
	
	wxBitmap m_bmpBackBuffer;
	wxMemoryDC m_dcBackBuffer;

	int m_nZoom;
	wxSize m_sizeVirtual;
	wxPoint m_ptOrigin;

	PieceInfo* m_pPieceInfo;
	ImageInfo* m_pImageInfo;

};
#endif // __IMAGEPIECEEDITOR_H__
