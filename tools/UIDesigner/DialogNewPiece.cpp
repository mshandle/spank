/*!
 * \file DialogNewPiece.cpp
 * \date 2011/10/12 12:09
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "DialogNewPiece.h"

IMPLEMENT_DYNAMIC_CLASS(DialogNewPiece, wxDialog)

BEGIN_EVENT_TABLE(DialogNewPiece, wxDialog)
	EVT_BUTTON(wxID_CANCEL, DialogNewPiece::OnButtonCancelClick)
	EVT_BUTTON(wxID_OK, DialogNewPiece::OnButtonEnterClick)
END_EVENT_TABLE()

DialogNewPiece::DialogNewPiece()
{
    Init();
}

DialogNewPiece::DialogNewPiece(wxWindow* parent, wxWindowID id /* = ID_UINEWIMAGEPIECEVIEW */, const wxString& caption /* = "New Piece" */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool DialogNewPiece::Create(wxWindow* parent, wxWindowID id /* = ID_UINEWIMAGEPIECEVIEW */, const wxString& caption /* = "New Piece" */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create(parent, id, caption, pos, size, style);
    CreateControls();
	if (GetSizer())
	{
		GetSizer()->SetSizeHints(this);
	}
    Centre();
    return true;
}

DialogNewPiece::~DialogNewPiece()
{
	//TODO:
}

void DialogNewPiece::Init()
{
	//TOOD:
	m_pTextCtrlFileName = NULL;
}

void DialogNewPiece::CreateControls()
{    
	DialogNewPiece* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* itemStaticText4 = new wxStaticText(itemDialog1, wxID_STATIC, _("FileName"), wxDefaultPosition, wxDefaultSize, 0);
	itemStaticText4->SetName(_T(".xml"));
	itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlFileName = new wxTextCtrl(itemDialog1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(m_pTextCtrlFileName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer6 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	wxButton* itemButton7 = new wxButton(itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer6->AddButton(itemButton7);

	wxButton* itemButton8 = new wxButton(itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer6->AddButton(itemButton8);

	itemStdDialogButtonSizer6->Realize();
}

void DialogNewPiece::OnButtonEnterClick(wxCommandEvent& event)
{
	if(m_pTextCtrlFileName->GetValue().empty())
		EndModal(wxID_CANCEL);
	EndModal(wxID_OK);
    event.Skip();
}

void DialogNewPiece::OnButtonCancelClick(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
	event.Skip();
}

wxString DialogNewPiece::GetValue()
{
	return m_pTextCtrlFileName->GetValue();
}
