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

protected:
	virtual wxSize CalculateVirtualSize();
	virtual void render();

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

private:
	wxBitmap m_bmpBackBuffer;
	wxMemoryDC m_dcBackBuffer;

	int m_nZoom;
	wxSize m_sizeVirtual;
	wxPoint m_ptOrigin;

};
#endif // __BASEEDITOR_H__
