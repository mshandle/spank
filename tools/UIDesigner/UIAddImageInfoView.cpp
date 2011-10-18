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

    EVT_BUTTON( ID_ButtonOk, UIAddImageInfoView::OnButtonOkClick )
    EVT_BUTTON( ID_BUTTONCANCEL, UIAddImageInfoView::OnButtoncancelClick )
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

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("FileName"), wxPoint(20, 20), wxDefaultSize, 0 );
    m_pTextCtrlFileName = new wxTextCtrl( itemDialog1, ID_FILENAME, wxEmptyString, wxPoint(80, 20), wxDefaultSize, 0 );

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("ImageID"), wxPoint(20, 60), wxDefaultSize, 0 );
    m_pTextCtrlImageID = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, wxEmptyString, wxPoint(80, 60), wxDefaultSize, 0 );

    wxButton* itemButton7 = new wxButton( itemDialog1, ID_ButtonOk, _("Enter"), wxPoint(-1, 160), wxDefaultSize, 0 );
    wxButton* itemButton8 = new wxButton( itemDialog1, ID_BUTTONCANCEL, _("Cancel"), wxPoint(200, 160), wxDefaultSize, 0 );
    wxButton* itemButton9 = new wxButton( itemDialog1, ID_BUTTONBROW, _("Browse"), wxPoint(200, 20), wxDefaultSize, 0 );

}

void UIAddImageInfoView::OnButtonOkClick( wxCommandEvent& event )
{
	EndDialog(wxOK);
    event.Skip();
}

void UIAddImageInfoView::OnButtoncancelClick( wxCommandEvent& event )
{
	EndDialog(wxCANCEL);
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
