/*!
 * \file UITipsDialogView.h
 * \date 2011/10/12 16:29
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __UITIPSDIALOGVIEW_H__
#define __UITIPSDIALOGVIEW_H__


#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>
#include "UIImagePieceDocument.h"

#define SYMBOL_UITIPSDIALOGVIEW_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_UITIPSDIALOGVIEW_TITLE _("UITipsDialogView")
#define SYMBOL_UITIPSDIALOGVIEW_IDNAME ID_UITIPSDIALOGVIEW
#define SYMBOL_UITIPSDIALOGVIEW_SIZE wxSize(280, 180)
#define SYMBOL_UITIPSDIALOGVIEW_POSITION wxDefaultPosition

class UITipsDialog: public wxDialog
{
public:
	enum CONTROL_ID
	{
	 ID_UITIPSDIALOGVIEW  = 10019,
	 ID_BUTTONYES,
	 ID_BUTTON 
	};
	DECLARE_DYNAMIC_CLASS( UITipsDialogView )
	DECLARE_EVENT_TABLE()

public:
	/// Constructors
	UITipsDialog();
	UITipsDialog( wxWindow* parent, wxWindowID id = SYMBOL_UITIPSDIALOGVIEW_IDNAME, const wxString& caption = SYMBOL_UITIPSDIALOGVIEW_TITLE, const wxPoint& pos = SYMBOL_UITIPSDIALOGVIEW_POSITION, const wxSize& size = SYMBOL_UITIPSDIALOGVIEW_SIZE, long style = SYMBOL_UITIPSDIALOGVIEW_STYLE );
	bool Create( wxWindow* parent, wxWindowID id = SYMBOL_UITIPSDIALOGVIEW_IDNAME, const wxString& caption = SYMBOL_UITIPSDIALOGVIEW_TITLE, const wxPoint& pos = SYMBOL_UITIPSDIALOGVIEW_POSITION, const wxSize& size = SYMBOL_UITIPSDIALOGVIEW_SIZE, long style = SYMBOL_UITIPSDIALOGVIEW_STYLE );

	~UITipsDialog();
	void Init();
	void CreateControls();
	void OnButtonyesClick( wxCommandEvent& event );
	void OnButtonClick( wxCommandEvent& event );
};

#endif // __UITIPSDIALOGVIEW_H__