/*!
 * \file DialogAddPiece.h
 * \date 2011/10/12 12:03
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __DIALOGADDPIECE_H__
#define __DIALOGADDPIECE_H__

#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>
#include "UIImagePieceDocument.h"

class DialogAddPiece : public wxDialog
{
	DECLARE_DYNAMIC_CLASS(DialogAddPiece)
	DECLARE_EVENT_TABLE()

public:
	enum CONTROL_ID
	{
		ID_DIALOGADDPIECE = 10012,
		ID_TEXTCTRL2 = 10013,
		ID_TEXTCTRL3 = 10014,
		ID_TEXTCTRL4 = 10015,
		ID_TEXTCTRL5 = 10016,
		ID_TEXTCTRL6 = 10017,
		ID_TEXTCTRL7 = 10024
	};

public:
	DialogAddPiece();
	DialogAddPiece(wxWindow* parent, wxWindowID id = ID_DIALOGADDPIECE, const wxString& caption = wxT("Add Piece"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	virtual ~DialogAddPiece();
	
	bool Create(wxWindow* parent, wxWindowID id = ID_DIALOGADDPIECE, const wxString& caption = wxT("Add Piece"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	
	void Init();
	void CreateControls();
	void OnClose(wxCommandEvent& event);
	void OnAdd(wxCommandEvent& event);
	UIImagePieceDocument::PIECE_INFO GetValue();

private:
	wxTextCtrl* m_pTxtImageId;
	wxTextCtrl* m_pTxtPieceId;
	wxTextCtrl* m_pTxtX;
	wxTextCtrl* m_pTxtY;
	wxTextCtrl* m_pTxtWidth;
	wxTextCtrl* m_pTxtHeight;
	UIImagePieceDocument::PIECE_INFO m_PieceInfo;

};
#endif // __DIALOGADDPIECE_H__
