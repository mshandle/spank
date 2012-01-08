/*!
 * \file DialogImportPiece.cpp
 * \date 2011/10/14 9:34
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "DialogImportPiece.h"

IMPLEMENT_DYNAMIC_CLASS(DialogImportPiece, wxDialog)

BEGIN_EVENT_TABLE(DialogImportPiece, wxDialog)
    EVT_BUTTON(ID_BUTTONBROW, DialogImportPiece::OnButtonbrowClick)
    EVT_BUTTON(ID_BUTTONENTRY, DialogImportPiece::OnButtonentryClick)
    EVT_BUTTON(ID_BUTTONCANCL, DialogImportPiece::OnButtoncanclClick)
END_EVENT_TABLE()

DialogImportPiece::DialogImportPiece()
{
    Init();
}

DialogImportPiece::DialogImportPiece(wxWindow* parent, wxWindowID id /* = ID_IMPORTPIECEVIEW */, const wxString& caption /* = wxT("ImportPieceView") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool DialogImportPiece::Create(wxWindow* parent, wxWindowID id /* = ID_IMPORTPIECEVIEW */, const wxString& caption /* = wxT("ImportPieceView") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create(parent, id, caption, pos, size, style);
    CreateControls();
    Centre();
    return true;
}

DialogImportPiece::~DialogImportPiece()
{
	//TODO:
}
void DialogImportPiece::Init()
{
    m_FilePath = NULL;
    m_pBackBitmapID = NULL;
}

void DialogImportPiece::CreateControls()
{    
    DialogImportPiece* itemDialog1 = this;

    wxStaticText* itemStaticText2 = new wxStaticText(itemDialog1, wxID_STATIC, _("FileName"), wxPoint(20, 20), wxDefaultSize, 0);
    m_FilePath = new wxTextCtrl(itemDialog1, ID_TEXTCTRL, wxEmptyString, wxPoint(80, 20), wxDefaultSize, 0);
    wxButton* itemButton4 = new wxButton(itemDialog1, ID_BUTTONBROW, _("Brow"), wxPoint(200, 20), wxDefaultSize, 0);
    wxStaticText* itemStaticText5 = new wxStaticText(itemDialog1, wxID_STATIC, _("ImageID"), wxPoint(20, 60), wxDefaultSize, 0);
    m_pBackBitmapID = new wxTextCtrl(itemDialog1, ID_TEXTCTRL1, wxEmptyString, wxPoint(80, 60), wxDefaultSize, 0);
    m_pBackBitmapID->SetMaxLength(2);
    wxButton* itemButton7 = new wxButton(itemDialog1, ID_BUTTONENTRY, _("Entry"), wxPoint(-1, 140), wxDefaultSize, 0);
    wxButton* itemButton8 = new wxButton(itemDialog1, ID_BUTTONCANCL, _("Cancl"), wxPoint(200, 140), wxDefaultSize, 0);
   
	wxTextValidator validator(wxFILTER_NUMERIC);
	m_pBackBitmapID->SetValidator(validator);
}

void DialogImportPiece::OnButtonbrowClick(wxCommandEvent& event)
{
	wxFileDialog dialog(this, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("PNG files (*.png)|*.png"), wxFD_DEFAULT_STYLE);
	if (dialog .ShowModal() == wxID_OK)
	{
		m_FilePath->SetValue(dialog.GetFilename());
	}
}

void DialogImportPiece::OnButtonentryClick(wxCommandEvent& event)
{
	EndModal(wxID_OK);
    event.Skip();
}

void DialogImportPiece::OnButtoncanclClick(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
    event.Skip();
}

wxString DialogImportPiece::GetFilePath()
{
	return m_FilePath->GetValue();
}

int DialogImportPiece::GetImageId() const
{
	return wxAtoi(m_pBackBitmapID->GetValue());
}
