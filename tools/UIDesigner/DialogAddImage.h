/*!
 * \file DialogAddImage.h
 * \date 2011/10/12 12:08
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __DIALOGADDIMAGE_H__
#define __DIALOGADDIMAGE_H__

#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>
#include "UIImagePieceDocument.h"

class DialogAddImage : public wxDialog
{
	DECLARE_DYNAMIC_CLASS(DialogAddImage)
	DECLARE_EVENT_TABLE()

public:
	enum CONTROL_ID
	{
		ID_DIALOGADDIMAGE = 10008,
		ID_TEXTCTRL = 10009,
		ID_BUTTON = 10010,
		ID_TEXTCTRL1 = 10011
	};

public:
	DialogAddImage();
	DialogAddImage(wxWindow* parent, wxWindowID id = ID_DIALOGADDIMAGE, const wxString& caption = wxT("Add Image"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	virtual ~DialogAddImage();

	bool Create(wxWindow* parent, wxWindowID id = ID_DIALOGADDIMAGE, const wxString& caption = wxT("Add Image"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

	void Init();
	void CreateControls();
	UIImagePieceDocument::IMAGE_INFO GetValue();

private:
	void OnBtnOkClicked(wxCommandEvent& event);
	void OnBtnCancelClicked(wxCommandEvent& event);
	void OnBtnBrowseClicked(wxCommandEvent& event);

private:
	wxTextCtrl* m_pTextCtrlFileName;
	wxTextCtrl* m_pTextCtrlImageId;

};
#endif // __DIALOGADDIMAGE_H__
