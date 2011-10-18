/*!
 * \file UIImportPieceView.h
 * \date 2011/10/14 9:34
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UIIMPORTPIECEVIEW_H__
#define __UIIMPORTPIECEVIEW_H__

#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>

#define SYMBOL_IMPORTPIECEVIEW_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_IMPORTPIECEVIEW_TITLE _("ImportPieceView")
#define SYMBOL_IMPORTPIECEVIEW_IDNAME ID_IMPORTPIECEVIEW
#define SYMBOL_IMPORTPIECEVIEW_SIZE wxSize(300, 200)
#define SYMBOL_IMPORTPIECEVIEW_POSITION wxDefaultPosition

class UIImportPieceView: public wxDialog
{    
public:
	enum CONTANCE_ID
	{
		 ID_IMPORTPIECEVIEW =  10080,
		 ID_TEXTCTRL,
		 ID_BUTTONBROW,
		 ID_TEXTCTRL1,
		 ID_BUTTONENTRY,
		 ID_BUTTONCANCL,
		 ID_TEXTCTRL2,
	};
	DECLARE_DYNAMIC_CLASS( UIImportPieceView )
	DECLARE_EVENT_TABLE()
public:
	UIImportPieceView();
	UIImportPieceView( wxWindow* parent, wxWindowID id = SYMBOL_IMPORTPIECEVIEW_IDNAME, const wxString& caption = SYMBOL_IMPORTPIECEVIEW_TITLE, const wxPoint& pos = SYMBOL_IMPORTPIECEVIEW_POSITION, const wxSize& size = SYMBOL_IMPORTPIECEVIEW_SIZE, long style = SYMBOL_IMPORTPIECEVIEW_STYLE );
	bool Create( wxWindow* parent, wxWindowID id = SYMBOL_IMPORTPIECEVIEW_IDNAME, const wxString& caption = SYMBOL_IMPORTPIECEVIEW_TITLE, const wxPoint& pos = SYMBOL_IMPORTPIECEVIEW_POSITION, const wxSize& size = SYMBOL_IMPORTPIECEVIEW_SIZE, long style = SYMBOL_IMPORTPIECEVIEW_STYLE );
	~UIImportPieceView();

public:
	wxString GetFilePath();
	int GetImageID();
private:
	void Init();
	void CreateControls();
	void OnButtonbrowClick( wxCommandEvent& event );
	void OnButtonentryClick( wxCommandEvent& event );
	void OnButtoncanclClick( wxCommandEvent& event );
private:
	wxTextCtrl* m_FilePath;
	wxTextCtrl* m_pBackBitmapID;

};

#endif // __UIIMPORTPIECEVIEW_H__