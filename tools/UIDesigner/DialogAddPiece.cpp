/*!
 * \file DialogAddPiece.cpp
 * \date 1-08-2012 14:09:39
 * 
 * 
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "DialogAddPiece.h"
#include "UIImagePieceDocument.h"

IMPLEMENT_DYNAMIC_CLASS(DialogAddPiece, wxDialog)
BEGIN_EVENT_TABLE(DialogAddPiece, wxDialog)
	EVT_BUTTON(wxID_CANCEL, DialogAddPiece::OnClose)
	EVT_BUTTON(wxID_OK, DialogAddPiece::OnAdd)
END_EVENT_TABLE()

DialogAddPiece::DialogAddPiece()
{
	 Init();
}

DialogAddPiece::DialogAddPiece(wxWindow* parent, wxWindowID id /* = ID_ADDIMAGEDIALOG */, const wxString& caption /* = wxT("Add Piece") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}

DialogAddPiece::~DialogAddPiece()
{
	//TODO:
}

bool DialogAddPiece::Create(wxWindow* parent, wxWindowID id /* = ID_ADDIMAGEDIALOG */, const wxString& caption /* = wxT("Add Piece") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
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

void DialogAddPiece::Init()
{
	//TODO:	
}

void DialogAddPiece::CreateControls()
{
	DialogAddPiece* itemDialog1 = this;
	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_RIGHT|wxALL, 5);
	wxTextValidator validator(wxFILTER_NUMERIC); 
	wxStaticText* itemStaticText4 = new wxStaticText(itemDialog1, wxID_STATIC, _("ImageID"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlImageID = new wxTextCtrl(itemDialog1, ID_IMAGEINPUT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 ,validator);
	itemBoxSizer3->Add(m_pTextCtrlImageID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer6, 0, wxALIGN_RIGHT|wxALL, 5);

	wxStaticText* itemStaticText7 = new wxStaticText(itemDialog1, wxID_STATIC, _("PieceName"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer6->Add(itemStaticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlStrID = new wxTextCtrl(itemDialog1, ID_IMAGENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer6->Add(m_pTextCtrlStrID, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer9, 0, wxALIGN_RIGHT|wxALL, 5);

	wxStaticText* itemStaticText10 = new wxStaticText(itemDialog1, wxID_STATIC, _("X"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer9->Add(itemStaticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextX = new wxTextCtrl(itemDialog1, ID_IMAGEX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 ,validator);
	itemBoxSizer9->Add(m_pTextX, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer12, 0, wxALIGN_RIGHT|wxALL, 5);

	wxStaticText* itemStaticText13 = new wxStaticText(itemDialog1, wxID_STATIC, _("Y"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer12->Add(itemStaticText13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlY = new wxTextCtrl(itemDialog1, ID_IMAGEY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, validator);
	itemBoxSizer12->Add(m_pTextCtrlY, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer15, 0, wxALIGN_RIGHT|wxALL, 5);

	wxStaticText* itemStaticText16 = new wxStaticText(itemDialog1, wxID_STATIC, _("Width"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer15->Add(itemStaticText16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlWidth = new wxTextCtrl(itemDialog1, ID_IMAGEWIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, validator);
	itemBoxSizer15->Add(m_pTextCtrlWidth, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer18, 0, wxALIGN_RIGHT|wxALL, 5);

	wxStaticText* itemStaticText19 = new wxStaticText(itemDialog1, wxID_STATIC, _("Height"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer18->Add(itemStaticText19, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_pTextCtrlHeight = new wxTextCtrl(itemDialog1, ID_IMAGEHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, validator);
	itemBoxSizer18->Add(m_pTextCtrlHeight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer21 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer21, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	wxButton* itemButton22 = new wxButton(itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer21->AddButton(itemButton22);

	wxButton* itemButton23 = new wxButton(itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer21->AddButton(itemButton23);

	itemStdDialogButtonSizer21->Realize();
}	

void DialogAddPiece::OnClose(wxCommandEvent& event)
{
	EndModal(wxCANCEL);
}

void DialogAddPiece::OnAdd(wxCommandEvent& event)
{
	wxString Strvalue = m_pTextX->GetValue();
	if(Strvalue.empty()) 
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.x = wxAtoi(Strvalue);
	m_pTextX->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlY->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.y = wxAtoi(Strvalue);
	m_pTextCtrlY->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlWidth->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.width = wxAtoi(Strvalue);
	m_pTextCtrlWidth->Clear();
	Strvalue.Clear();
	
	Strvalue = m_pTextCtrlHeight->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.height = wxAtoi(Strvalue);
	m_pTextCtrlHeight->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlImageID->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.nImageId = wxAtoi(Strvalue);
	m_pTextCtrlImageID->Clear();
	Strvalue.Clear();

	Strvalue = m_pTextCtrlStrID->GetValue();
	if(Strvalue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.strId = Strvalue;
	m_pTextCtrlStrID->Clear();
	Strvalue.Clear();

	EndModal(wxID_OK);
}

UIImagePieceDocument::PIECE_INFO DialogAddPiece::GetValue() 
{
	return m_PieceInfo;
}
