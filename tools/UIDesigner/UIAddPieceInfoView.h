/*!
 * \file UIAddPieceInfoView.h
 * \date 2011/10/12 12:03
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UIADDPIECEINFOVIEW_H__
#define __UIADDPIECEINFOVIEW_H__



#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>
#include "UIImagePieceDocument.h"


#define SYMBOL_ADDIMAGEDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_ADDIMAGEDIALOG_TITLE _("AddImageDialog")
#define SYMBOL_ADDIMAGEDIALOG_IDNAME ID_ADDIMAGEDIALOG
#define SYMBOL_ADDIMAGEDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_ADDIMAGEDIALOG_POSITION wxDefaultPosition


class AddImageDialog :
	public wxDialog
{
public:
	enum
	{
		 ID_ADDIMAGEDIALOG =10000,
		 ID_IMAGEINPUT,
		 ID_IMAGEX,
		 ID_IMAGEY,
		 ID_IMAGEWIDTH,
		 ID_IMAGEHEIGHT,
		 ID_IMAGENAME,
	};
	DECLARE_DYNAMIC_CLASS( AddImageDialog )
	DECLARE_EVENT_TABLE()
public:
	AddImageDialog(void);
	AddImageDialog( wxWindow* parent, wxWindowID id = SYMBOL_ADDIMAGEDIALOG_IDNAME, const wxString& caption = SYMBOL_ADDIMAGEDIALOG_TITLE, const wxPoint& pos = SYMBOL_ADDIMAGEDIALOG_POSITION, const wxSize& size = SYMBOL_ADDIMAGEDIALOG_SIZE, long style = wxDEFAULT_DIALOG_STYLE );
	
	bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ADDIMAGEDIALOG_IDNAME, const wxString& caption = SYMBOL_ADDIMAGEDIALOG_TITLE, const wxPoint& pos = SYMBOL_ADDIMAGEDIALOG_POSITION, const wxSize& size = SYMBOL_ADDIMAGEDIALOG_SIZE, long style = wxDEFAULT_DIALOG_STYLE );
	
	~AddImageDialog(void);
	
	void Init();
	void CreateControls();
	void OnClose(wxCommandEvent& event);
	void OnAdd(wxCommandEvent& event);
	UIImagePieceDocument::PIECE_INFO GetValue();
private:
	wxTextCtrl* m_pTextX;
	wxTextCtrl* m_pTextCtrlY;
	wxTextCtrl* m_pTextCtrlWidth;
	wxTextCtrl* m_pTextCtrlHeight;
	wxTextCtrl* m_pTextCtrlImageID;
	wxTextCtrl* m_pTextCtrlStrID;
	UIImagePieceDocument::PIECE_INFO m_PieceInfo;
};


#endif // __UIADDPIECEINFOVIEW_H__