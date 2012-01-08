/*!
 * \file DialogNewPiece.h
 * \date 2011/10/12 12:10
 *	
 *	
 * \author:	wabaoqing(wbaoqing@gmail.com)
 */
#ifndef __DIALOGNEWPIECE_H__
#define __DIALOGNEWPIECE_H__

#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>

class DialogNewPiece : public wxDialog
{
	DECLARE_DYNAMIC_CLASS(DialogNewPiece)
	DECLARE_EVENT_TABLE()

public:
	enum CONTROL_ID
	{
		ID_DIALOG_NEW_PIECE = 10040,
		ID_TEXTCTRL1,
	};

public:
	DialogNewPiece();
	DialogNewPiece(wxWindow* parent, wxWindowID id = ID_DIALOG_NEW_PIECE, const wxString& caption = "New Piece", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	virtual ~DialogNewPiece();

	bool Create(wxWindow* parent, wxWindowID id = ID_DIALOG_NEW_PIECE, const wxString& caption = "New Piece", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	void Init();
	void CreateControls();
	wxString GetValue();

private:
	void OnButtonEnterClick(wxCommandEvent& event);
	void OnButtonCancelClick(wxCommandEvent& event);

private:
	wxTextCtrl* m_pTextCtrlFileName;

};
#endif // __DIALOGNEWPIECE_H__
