/*!
 * \file DialogAddImage.cpp
 * \date 2011/10/12 12:07
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#include "DialogAddImage.h"

IMPLEMENT_DYNAMIC_CLASS(DialogAddImage, wxDialog)

BEGIN_EVENT_TABLE(DialogAddImage, wxDialog)
    EVT_BUTTON(wxID_OK, DialogAddImage::OnBtnOkClicked)
    EVT_BUTTON(wxID_CANCEL, DialogAddImage::OnBtnCancelClicked)
    EVT_BUTTON(ID_BUTTONBROW, DialogAddImage::OnBtnBrowseClicked)
END_EVENT_TABLE()


DialogAddImage::DialogAddImage()
{
    Init();
}

DialogAddImage::DialogAddImage(wxWindow* parent, wxWindowID id /* = ID_UIADDIMAGEINFOVIEW */, const wxString& caption /* = "Add Image" */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

DialogAddImage::~DialogAddImage()
{
	//TODO:
}

bool DialogAddImage::Create(wxWindow* parent, wxWindowID id /* = ID_UIADDIMAGEINFOVIEW */, const wxString& caption /* = "Add Image" */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
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

void DialogAddImage::Init()
{
    m_pTextCtrlFileName = NULL;
    m_pTextCtrlImageId = NULL;
}

void DialogAddImage::CreateControls()
{
	DialogAddImage* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* itemStaticText4 = new wxStaticText(itemDialog1, wxID_STATIC, wxT("FileName"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlFileName = new wxTextCtrl(itemDialog1, ID_FILENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(m_pTextCtrlFileName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* itemButton6 = new wxButton(itemDialog1, ID_BUTTONBROW, wxT("Brow"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer7, 0, wxALIGN_LEFT|wxALL, 5);

	wxStaticText* itemStaticText8 = new wxStaticText(itemDialog1, wxID_STATIC, wxT("ImageID"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer7->Add(itemStaticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlImageId = new wxTextCtrl(itemDialog1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer7->Add(m_pTextCtrlImageId, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer10 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	wxButton* itemButton11 = new wxButton(itemDialog1, wxID_OK, wxT("&OK"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer10->AddButton(itemButton11);

	wxButton* itemButton12 = new wxButton(itemDialog1, wxID_CANCEL, wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer10->AddButton(itemButton12);

	itemStdDialogButtonSizer10->Realize();
}

void DialogAddImage::OnBtnOkClicked(wxCommandEvent& event)
{
	EndDialog(wxID_OK);
    event.Skip();
}

void DialogAddImage::OnBtnCancelClicked(wxCommandEvent& event)
{
	EndDialog(wxID_CANCEL);
    event.Skip();
}

void DialogAddImage::OnBtnBrowseClicked(wxCommandEvent& event)
{
	wxFileDialog dialog(this, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("PNG files (*.png)|*.png"), wxFD_DEFAULT_STYLE);
	if (dialog .ShowModal() == wxID_OK)
	{
		wxString strPath = dialog.GetFilename();
		m_pTextCtrlFileName->SetValue(strPath);
	}
    event.Skip();
}

UIImagePieceDocument::IMAGE_INFO DialogAddImage::GetValue()
{
	UIImagePieceDocument::IMAGE_INFO ImageInfo;
	ImageInfo.strFile = m_pTextCtrlFileName->GetValue();
	ImageInfo.nId = wxAtoi(m_pTextCtrlImageId->GetValue());
	return ImageInfo;
}
