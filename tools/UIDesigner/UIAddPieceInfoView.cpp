#include "UIAddPieceInfoView.h"
#include "UIImagePieceDocument.h"

IMPLEMENT_DYNAMIC_CLASS( AddImageDialog, wxDialog )
BEGIN_EVENT_TABLE( AddImageDialog, wxDialog )
 EVT_BUTTON(wxID_CLOSE, AddImageDialog::OnClose)
 EVT_BUTTON(wxID_ADD, AddImageDialog::OnAdd)
END_EVENT_TABLE()

AddImageDialog::AddImageDialog(void)
{
	 Init();
}

AddImageDialog::AddImageDialog(wxWindow* parent, wxWindowID id /*= SYMBOL_ADDIMAGEDIALOG_IDNAME*/, const wxString& caption /*= SYMBOL_ADDIMAGEDIALOG_TITLE*/, const wxPoint& pos /*= SYMBOL_ADDIMAGEDIALOG_POSITION*/, const wxSize& size /*= SYMBOL_ADDIMAGEDIALOG_SIZE*/, long style /*= SYMBOL_ADDIMAGEDIALOG_STYLE */)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}
AddImageDialog::~AddImageDialog(void)
{
	//TODO:
}

bool AddImageDialog::Create(wxWindow* parent, wxWindowID id /*= SYMBOL_ADDIMAGEDIALOG_IDNAME*/, const wxString& caption /*= SYMBOL_ADDIMAGEDIALOG_TITLE*/, const wxPoint& pos /*= SYMBOL_ADDIMAGEDIALOG_POSITION*/, const wxSize& size /*= SYMBOL_ADDIMAGEDIALOG_SIZE*/, long style /*= SYMBOL_ADDIMAGEDIALOG_STYLE */)
{
	SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
	wxDialog::Create( parent, id, caption, pos, size, style );
	CreateControls();
	Centre();
	return true;
}

void AddImageDialog::Init()
{
	//TODO:	
}

void AddImageDialog::CreateControls()
{
	AddImageDialog* itemDialog1 = this;
	wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("ImageID"), wxPoint(0, 0), wxSize(60, 20), 0 );
	wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("X"), wxPoint(0, 40), wxDefaultSize, 0 );
	wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("Y"), wxPoint(0, 80), wxDefaultSize, 0 );
	wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Width"), wxPoint(0, 120), wxDefaultSize, 0 );
	wxStaticText* itemStaticText9 = new wxStaticText(itemDialog1, wxID_STATIC, _("Height"), wxPoint(0, 160), wxDefaultSize, 0);
	wxTextValidator validator(wxFILTER_NUMERIC); 
	m_pTextX = new wxTextCtrl( itemDialog1, ID_IMAGEX, wxEmptyString, wxPoint(60, 40), wxDefaultSize, 0 ,validator);
	m_pTextCtrlY = new wxTextCtrl( itemDialog1, ID_IMAGEY, wxEmptyString, wxPoint(60, 80), wxDefaultSize, 0,validator );
	m_pTextCtrlWidth = new wxTextCtrl( itemDialog1, ID_IMAGEWIDTH, wxEmptyString, wxPoint(60, 120), wxDefaultSize, 0 ,validator);
	m_pTextCtrlImageID = new wxTextCtrl( itemDialog1, ID_IMAGEINPUT, wxEmptyString, wxPoint(60, 0), wxDefaultSize, 0 ,validator);
	m_pTextCtrlHeight = new wxTextCtrl( itemDialog1, ID_IMAGEHEIGHT, wxEmptyString, wxPoint(60, 160), wxDefaultSize, 0 ,validator);

	wxStaticText* itemStaticText10 = new wxStaticText(itemDialog1, wxID_STATIC, _("StrID"), wxPoint(0, 200), wxDefaultSize, 0);
	m_pTextCtrlStrID = new wxTextCtrl( itemDialog1, ID_IMAGENAME, wxEmptyString, wxPoint(60, 200), wxDefaultSize, 0 );

	wxButton* AddButton = new wxButton( itemDialog1, wxID_ADD, _("Add"), wxPoint(0, 230), wxSize(70, 30), 0 );
	AddButton->SetDefault();
	wxButton* CanclButtont = new wxButton( itemDialog1, wxID_CLOSE, _("Cancel"), wxPoint(120, 230), wxSize(70, 30), 0 );
	CanclButtont->SetDefault();
}	

void AddImageDialog::OnClose(wxCommandEvent& event)
{
	EndModal(wxCANCEL);
}

void AddImageDialog::OnAdd(wxCommandEvent& event)
{
	

	wxString Strvalue = m_pTextX->GetValue();
	if(Strvalue.empty()) 
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.rect.x = wxAtoi(Strvalue);
	m_pTextX->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlY->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.rect.y = wxAtoi(Strvalue);
	m_pTextCtrlY->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlWidth->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.rect.width = wxAtoi(Strvalue);
	m_pTextCtrlWidth->Clear();
	Strvalue.Clear();
	
	Strvalue = m_pTextCtrlHeight->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.rect.height = wxAtoi(Strvalue);
	m_pTextCtrlHeight->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlImageID->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.nImageID = wxAtoi(Strvalue);
	m_pTextCtrlImageID->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlStrID->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.strID = Strvalue;
	m_pTextCtrlStrID->Clear();
	Strvalue.Clear();

	EndModal(wxAPPLY);
}

UIImagePieceDocument::PIECE_INFO AddImageDialog::GetValue() 
{
	return m_PieceInfo;
}