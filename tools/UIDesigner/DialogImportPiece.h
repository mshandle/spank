/*!
 * \file DialogImportPiece.h
 * \date 2011/10/14 9:34
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __DIALOGIMPORTPIECE_H__
#define __DIALOGIMPORTPIECE_H__

#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/wx.h>

class DialogImportPiece : public wxDialog
{
	DECLARE_DYNAMIC_CLASS(DialogImportPiece)
	DECLARE_EVENT_TABLE()

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

public:
	DialogImportPiece();
	DialogImportPiece(wxWindow* parent, wxWindowID id = ID_IMPORTPIECEVIEW, const wxString& caption = wxT("ImportPieceView"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	virtual ~DialogImportPiece();

	virtual bool Create(wxWindow* parent, wxWindowID id = ID_IMPORTPIECEVIEW, const wxString& caption = wxT("ImportPieceView"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

	wxString GetFilePath();
	int GetImageId() const;

private:
	void Init();
	void CreateControls();
	void OnButtonbrowClick(wxCommandEvent& event);
	void OnButtonentryClick(wxCommandEvent& event);
	void OnButtoncanclClick(wxCommandEvent& event);

private:
	wxTextCtrl* m_FilePath;
	wxTextCtrl* m_pBackBitmapID;

};
#endif // __DIALOGIMPORTPIECE_H__
