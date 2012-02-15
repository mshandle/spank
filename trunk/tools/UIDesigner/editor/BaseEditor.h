/*!
 * \file BaseEditor.h
 * \date 2-14-2012 17:58:12
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BASEEDITOR_H__
#define __BASEEDITOR_H__

#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>

class BaseEditor : public wxWindow
{
	DECLARE_DYNAMIC_CLASS(BaseEditor)
	DECLARE_EVENT_TABLE()

public:
	enum CONST_DEFINE
	{
		SCROLL_LINE_DISTANCE = 10,
		ZOOM_MIN = 1,
		ZOOM_STEP = 1,
		ZOOM_MAX = 10,
		DEFAULT_VIRTUAL_SIZE = 100,
	};

public:
	BaseEditor();
	BaseEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual ~BaseEditor();

	bool Create(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual wxSize DoGetBestSize() const;

	bool ZoomIn();
	bool ZoomOut();
	bool Zoom(int zoom);
	int GetZoom() const;

	virtual wxSize CalculateVirtualSize();
	virtual wxSize CalculateMaxSize();

	virtual void Draw(wxDC& dc);
	virtual void OnLButtonDown(const wxPoint& pos);

	void UpdateVirtualSize();
	void UpdateScrollPosition(int x, int y);
	const wxPoint& GetOriginOffset() const;

	wxPoint CalculateZoomedPos(const wxPoint& pos);
	wxPoint CalculateOriginPos(const wxPoint& zoomedPos);

protected:
	void DrawBitmap(wxDC& dc, wxBitmap& bitmap, const wxPoint& destPos);
	void DrawRectangle(wxDC& dc, const wxRect& rect);
	void DrawLine(wxDC& dc, const wxPoint& pt1, const wxPoint& pt2);

private:
	void Init();
	void Release();

	void OnPaintEvt(wxPaintEvent& event);
	void OnMouseWheelEvt(wxMouseEvent& event);
	void OnLButtonDownEvt(wxMouseEvent& event);
	void OnSizeEvt(wxSizeEvent& event);

	void OnScrollLineUpEvt(wxScrollWinEvent& event);
	void OnScrollLineDownEvt(wxScrollWinEvent& event);
	void OnScrollPageUpEvt(wxScrollWinEvent& event);
	void OnScrollPageDownEvt(wxScrollWinEvent& event);
	void OnScrollThumbTrackEvt(wxScrollWinEvent& event);
	void OnScrollThumbReleaseEvt(wxScrollWinEvent& event);

private:
	int m_nZoom;
	wxSize m_ZoomedSize;
	wxPoint m_ptOriginOffset;
	wxMemoryDC m_memDC;

};
#endif // __BASEEDITOR_H__