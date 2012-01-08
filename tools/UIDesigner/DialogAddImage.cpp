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
    EVT_BUTTON(ID_BUTTON, DialogAddImage::OnBtnBrowseClicked)
END_EVENT_TABLE()


DialogAddImage::DialogAddImage()
{
    Init();
}

DialogAddImage::DialogAddImage(wxWindow* parent, wxWindowID id /* = ID_DIALOGADDIMAGE */, const wxString& caption /* = wxT("Add Image") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

DialogAddImage::~DialogAddImage()
{
	//TODO:
}

bool DialogAddImage::Create(wxWindow* parent, wxWindowID id /* = ID_DIALOGADDIMAGE */, const wxString& caption /* = wxT("Add Image") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
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

	wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(2, 3, 0, 0);
	itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* itemStaticText4 = new wxStaticText(itemDialog1, wxID_STATIC, _("File:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl5 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTextCtrlFileName = itemTextCtrl5;
	itemFlexGridSizer3->Add(itemTextCtrl5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* itemButton6 = new wxButton(itemDialog1, ID_BUTTON, _("Browser"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemButton6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* itemStaticText7 = new wxStaticText(itemDialog1, wxID_STATIC, _("Image Id:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl8 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTextCtrlImageId = itemTextCtrl8;
	itemFlexGridSizer3->Add(itemTextCtrl8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	itemFlexGridSizer3->AddGrowableCol(1);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer9 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	wxButton* itemButton10 = new wxButton(itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer9->AddButton(itemButton10);

	wxButton* itemButton11 = new wxButton(itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer9->AddButton(itemButton11);

	itemStdDialogButtonSizer9->Realize();

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
