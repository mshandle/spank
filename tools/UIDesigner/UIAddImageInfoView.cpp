/*!
 * \file UIAddImageInfoView.cpp
 * \date 2011/10/12 12:07
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#include "UIAddImageInfoView.h"


IMPLEMENT_DYNAMIC_CLASS( UIAddImageInfoView, wxDialog )

BEGIN_EVENT_TABLE( UIAddImageInfoView, wxDialog )

    EVT_BUTTON( wxID_OK, UIAddImageInfoView::OnButtonOkClick )
    EVT_BUTTON( wxID_CANCEL, UIAddImageInfoView::OnButtoncancelClick )
    EVT_BUTTON( ID_BUTTONBROW, UIAddImageInfoView::OnButtonbrowClick )

END_EVENT_TABLE()


UIAddImageInfoView::UIAddImageInfoView()
{
    Init();
}

UIAddImageInfoView::UIAddImageInfoView( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


bool UIAddImageInfoView::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );
    CreateControls();
	if (GetSizer())
	{
		GetSizer()->SetSizeHints(this);
	}
    Centre();
    return true;
}

UIAddImageInfoView::~UIAddImageInfoView()
{
	//TODO:
}

void UIAddImageInfoView::Init()
{
    m_pTextCtrlFileName = NULL;
    m_pTextCtrlImageID = NULL;
}

void UIAddImageInfoView::CreateControls()
{    

	UIAddImageInfoView* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("FileName"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlFileName = new wxTextCtrl( itemDialog1, ID_FILENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer3->Add(m_pTextCtrlFileName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* itemButton6 = new wxButton( itemDialog1, ID_BUTTONBROW, _("Brow"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer3->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer7, 0, wxALIGN_LEFT|wxALL, 5);

	wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("ImageID"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer7->Add(itemStaticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlImageID = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer7->Add(m_pTextCtrlImageID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer10 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
	itemStdDialogButtonSizer10->AddButton(itemButton11);

	wxButton* itemButton12 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	itemStdDialogButtonSizer10->AddButton(itemButton12);

	itemStdDialogButtonSizer10->Realize();
}

void UIAddImageInfoView::OnButtonOkClick( wxCommandEvent& event )
{
	EndDialog(wxID_OK);
    event.Skip();
}

void UIAddImageInfoView::OnButtoncancelClick( wxCommandEvent& event )
{
	EndDialog(wxID_CANCEL);
    event.Skip();
}

void UIAddImageInfoView::OnButtonbrowClick( wxCommandEvent& event )
{
	wxFileDialog dialog(this, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("PNG files (*.png)|*.png"), wxFD_DEFAULT_STYLE);
	if (dialog .ShowModal() == wxID_OK)
	{
		wxString strPath = dialog.GetFilename();
		m_pTextCtrlFileName->SetValue(strPath);
	}
    event.Skip();
}

UIImagePieceDocument::IMAGE_INFO UIAddImageInfoView::GetValue()
{
	UIImagePieceDocument::IMAGE_INFO ImageInfo;
	ImageInfo.strFile = m_pTextCtrlFileName->GetValue();
	ImageInfo.nID = wxAtoi(m_pTextCtrlImageID->GetValue());
	return ImageInfo;
}
