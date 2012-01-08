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
		 ID_ADDIMAGEDIALOG =10000,
		 ID_IMAGEINPUT,
		 ID_IMAGEX,
		 ID_IMAGEY,
		 ID_IMAGEWIDTH,
		 ID_IMAGEHEIGHT,
		 ID_IMAGENAME,
	};

public:
	DialogAddPiece();
	DialogAddPiece(wxWindow* parent, wxWindowID id = ID_ADDIMAGEDIALOG, const wxString& caption = wxT("Add Piece"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	virtual ~DialogAddPiece();
	
	bool Create(wxWindow* parent, wxWindowID id = ID_ADDIMAGEDIALOG, const wxString& caption = wxT("Add Piece"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	
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
#endif // __DIALOGADDPIECE_H__
