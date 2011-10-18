/*!
 * \file UITipsDialogView.cpp
 * \date 2011/10/12 16:29
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "UITipsDialogView.h"

IMPLEMENT_DYNAMIC_CLASS( UITipsDialog, wxDialog )


BEGIN_EVENT_TABLE( UITipsDialog, wxDialog )
    EVT_BUTTON( ID_BUTTONYES, UITipsDialog::OnButtonyesClick )
    EVT_BUTTON( ID_BUTTON, UITipsDialog::OnButtonClick )
END_EVENT_TABLE()


UITipsDialog::UITipsDialog()
{
    Init();
}

UITipsDialog::UITipsDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


bool UITipsDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();

    return true;
}

UITipsDialog::~UITipsDialog()
{
	//TODO:
}
void UITipsDialog::Init()
{
	//TODO:
}

void UITipsDialog::CreateControls()
{    
    UITipsDialog* itemDialog1 = this;
    wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("   The File has Change! \nDo you want to save it?"), wxPoint(60, 20), wxDefaultSize, 0 );
    wxButton* itemButton3 = new wxButton( itemDialog1, ID_BUTTONYES, _("YES"), wxPoint(10, 120), wxDefaultSize, 0 );
    wxButton* itemButton4 = new wxButton( itemDialog1, ID_BUTTON, _("ON"), wxPoint(180, 120), wxDefaultSize, 0 );
}

void UITipsDialog::OnButtonyesClick( wxCommandEvent& event )
{
	EndModal(wxID_YES);
    event.Skip();
}

void UITipsDialog::OnButtonClick( wxCommandEvent& event )
{
	EndModal(wxID_CANCEL);
    event.Skip();
}

