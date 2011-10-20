/*!
 * \file UIAddImageInfoView.h
 * \date 2011/10/12 12:08
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __UIADDIMAGEINFOVIEW_H__
#define __UIADDIMAGEINFOVIEW_H__

#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>
#include "UIImagePieceDocument.h"

#define SYMBOL_UIADDIMAGEINFOVIEW_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_UIADDIMAGEINFOVIEW_TITLE _("UIAddImageInfoView")
#define SYMBOL_UIADDIMAGEINFOVIEW_IDNAME ID_UIADDIMAGEINFOVIEW
#define SYMBOL_UIADDIMAGEINFOVIEW_SIZE wxSize(400, 300)
#define SYMBOL_UIADDIMAGEINFOVIEW_POSITION wxDefaultPosition

class UIAddImageInfoView :public wxDialog
{
	DECLARE_DYNAMIC_CLASS( UIAddImageInfoView )
	DECLARE_EVENT_TABLE()
public:
	enum CONTROL_ID
	{
		 ID_UIADDIMAGEINFOVIEW = 10000,
		 ID_FILENAME,
		 ID_TEXTCTRL ,
		 ID_BUTTONBROW,
	};
public:
	   UIAddImageInfoView();
	   UIAddImageInfoView( wxWindow* parent, wxWindowID id = SYMBOL_UIADDIMAGEINFOVIEW_IDNAME, const wxString& caption = SYMBOL_UIADDIMAGEINFOVIEW_TITLE, const wxPoint& pos = SYMBOL_UIADDIMAGEINFOVIEW_POSITION, const wxSize& size = SYMBOL_UIADDIMAGEINFOVIEW_SIZE, long style = SYMBOL_UIADDIMAGEINFOVIEW_STYLE );
	   bool Create( wxWindow* parent, wxWindowID id = SYMBOL_UIADDIMAGEINFOVIEW_IDNAME, const wxString& caption = SYMBOL_UIADDIMAGEINFOVIEW_TITLE, const wxPoint& pos = SYMBOL_UIADDIMAGEINFOVIEW_POSITION, const wxSize& size = SYMBOL_UIADDIMAGEINFOVIEW_SIZE, long style = SYMBOL_UIADDIMAGEINFOVIEW_STYLE );

	   ~UIAddImageInfoView();
		void Init();
		void CreateControls();
		void OnButtonOkClick( wxCommandEvent& event );
		void OnButtoncancelClick( wxCommandEvent& event );
		void OnButtonbrowClick( wxCommandEvent& event );
		UIImagePieceDocument::IMAGE_INFO GetValue();
private:
		 wxTextCtrl* m_pTextCtrlFileName;
		 wxTextCtrl* m_pTextCtrlImageID;
};
#endif // __UIADDIMAGEINFOVIEW_H__