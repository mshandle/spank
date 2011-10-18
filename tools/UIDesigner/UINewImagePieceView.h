/*!
 * \file UINewImagePieceView.h
 * \date 2011/10/12 12:10
 *	
 *	
 * \author:	wabaoqing(wbaoqing@gmail.com)
 */
#ifndef __UINEWIMAGEPIECEVIEW_H__
#define __UINEWIMAGEPIECEVIEW_H__

#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>

#define SYMBOL_UINEWIMAGEPIECEVIEW_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_UINEWIMAGEPIECEVIEW_TITLE _("UINewImagePieceView")
#define SYMBOL_UINEWIMAGEPIECEVIEW_IDNAME ID_UINEWIMAGEPIECEVIEW
#define SYMBOL_UINEWIMAGEPIECEVIEW_SIZE wxSize(260, 200)
#define SYMBOL_UINEWIMAGEPIECEVIEW_POSITION wxDefaultPosition

class UINewImagePieceView : public wxDialog
{

public:
	enum CONTROL_ID
	{
	 ID_UINEWIMAGEPIECEVIEW = 10040,
	 ID_TEXTCTRL1,
	 ID_BUTTONENTER,
	 ID_BUTTONCANCEL
	};

	DECLARE_DYNAMIC_CLASS( UINewImagePieceView )
	DECLARE_EVENT_TABLE()

public:

	UINewImagePieceView();
	UINewImagePieceView( wxWindow* parent, wxWindowID id = SYMBOL_UINEWIMAGEPIECEVIEW_IDNAME, const wxString& caption = SYMBOL_UINEWIMAGEPIECEVIEW_TITLE, const wxPoint& pos = SYMBOL_UINEWIMAGEPIECEVIEW_POSITION, const wxSize& size = SYMBOL_UINEWIMAGEPIECEVIEW_SIZE, long style = SYMBOL_UINEWIMAGEPIECEVIEW_STYLE );
	bool Create( wxWindow* parent, wxWindowID id = SYMBOL_UINEWIMAGEPIECEVIEW_IDNAME, const wxString& caption = SYMBOL_UINEWIMAGEPIECEVIEW_TITLE, const wxPoint& pos = SYMBOL_UINEWIMAGEPIECEVIEW_POSITION, const wxSize& size = SYMBOL_UINEWIMAGEPIECEVIEW_SIZE, long style = SYMBOL_UINEWIMAGEPIECEVIEW_STYLE );
	~UINewImagePieceView();
	void Init();
	void CreateControls();
	wxString GetValue();
private:
	void OnButtonEnterClick( wxCommandEvent& event );
	void OnButtonCancelClick( wxCommandEvent& event );
private:
	wxTextCtrl* m_pTextCtrlFileName;
};	
#endif // __UINEWIMAGEPIECEVIEW_H__