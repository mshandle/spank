/*!
 * \file UINewImagePieceView.cpp
 * \date 2011/10/12 12:09
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "UINewImagePieceView.h"

IMPLEMENT_DYNAMIC_CLASS( UINewImagePieceView, wxDialog )

BEGIN_EVENT_TABLE( UINewImagePieceView, wxDialog )
	EVT_BUTTON(ID_BUTTONCANCEL, UINewImagePieceView::OnButtonCancelClick)
	EVT_BUTTON(ID_BUTTONENTER, UINewImagePieceView::OnButtonEnterClick)
END_EVENT_TABLE()

UINewImagePieceView::UINewImagePieceView()
{
    Init();
}

UINewImagePieceView::UINewImagePieceView( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool UINewImagePieceView::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );
    CreateControls();
    Centre();
    return true;
}

UINewImagePieceView::~UINewImagePieceView()
{
	//TODO:
}

void UINewImagePieceView::Init()
{
	//TOOD:
	m_pTextCtrlFileName = NULL;
}

void UINewImagePieceView::CreateControls()
{    
    UINewImagePieceView* itemDialog1 = this;

    wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("FileName"), wxPoint(20, 40), wxDefaultSize, 0 );
    m_pTextCtrlFileName = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, wxEmptyString, wxPoint(80, 40), wxSize(120, -1), 0 );

    wxButton* itemButton4 = new wxButton( itemDialog1, ID_BUTTONENTER, _("Enter"), wxPoint(-1, 120), wxDefaultSize, 0 );
    wxButton* itemButton5 = new wxButton( itemDialog1, ID_BUTTONCANCEL, _("Cancel"), wxPoint(160, 120), wxSize(74, 24), 0 );
}

void UINewImagePieceView::OnButtonEnterClick( wxCommandEvent& event )
{
	if(m_pTextCtrlFileName->GetValue().empty())
		EndModal(wxID_CANCEL);
	EndModal(wxID_OK);
    event.Skip();
}

void UINewImagePieceView::OnButtonCancelClick( wxCommandEvent& event )
{
	EndModal(wxID_CANCEL);
	event.Skip();
}

wxString UINewImagePieceView::GetValue()
{
	return m_pTextCtrlFileName->GetValue();
}
