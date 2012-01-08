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

DialogAddPiece::DialogAddPiece(wxWindow* parent, wxWindowID id /* = ID_DIALOGADDPIECE */, const wxString& caption /* = wxT("Add Piece") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}

DialogAddPiece::~DialogAddPiece()
{
	//TODO:
}

bool DialogAddPiece::Create(wxWindow* parent, wxWindowID id /* = ID_DIALOGADDPIECE */, const wxString& caption /* = wxT("Add Piece") */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = wxDEFAULT_DIALOG_STYLE */)
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
	m_pTxtImageId = NULL;
	m_pTxtPieceId = NULL;
	m_pTxtX = NULL;
	m_pTxtY = NULL;
	m_pTxtWidth = NULL;
	m_pTxtHeight = NULL;
}

void DialogAddPiece::CreateControls()
{
	DialogAddPiece* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(6, 2, 0, 0);
	itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* itemStaticText4 = new wxStaticText(itemDialog1, wxID_STATIC, _("Image Id:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl5 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTxtImageId = itemTextCtrl5;
	itemFlexGridSizer3->Add(itemTextCtrl5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* itemStaticText6 = new wxStaticText(itemDialog1, wxID_STATIC, _("Piece Id:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl7 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTxtPieceId = itemTextCtrl7;
	itemFlexGridSizer3->Add(itemTextCtrl7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* itemStaticText8 = new wxStaticText(itemDialog1, wxID_STATIC, _("X:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl9 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTxtX = itemTextCtrl9;
	itemFlexGridSizer3->Add(itemTextCtrl9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* itemStaticText10 = new wxStaticText(itemDialog1, wxID_STATIC, _("Y:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText10, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl11 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTxtY = itemTextCtrl11;
	itemFlexGridSizer3->Add(itemTextCtrl11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* itemStaticText12 = new wxStaticText(itemDialog1, wxID_STATIC, _("Width:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl13 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTxtWidth = itemTextCtrl13;
	itemFlexGridSizer3->Add(itemTextCtrl13, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* itemStaticText14 = new wxStaticText(itemDialog1, wxID_STATIC, _("Height:"), wxDefaultPosition, wxDefaultSize, 0);
	itemFlexGridSizer3->Add(itemStaticText14, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl15 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 0);
	m_pTxtHeight = itemTextCtrl15;
	itemFlexGridSizer3->Add(itemTextCtrl15, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	itemFlexGridSizer3->AddGrowableCol(1);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer16 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	wxButton* itemButton17 = new wxButton(itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer16->AddButton(itemButton17);

	wxButton* itemButton18 = new wxButton(itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer16->AddButton(itemButton18);

	itemStdDialogButtonSizer16->Realize();
}	

void DialogAddPiece::OnClose(wxCommandEvent& event)
{
	EndModal(wxCANCEL);
}

void DialogAddPiece::OnAdd(wxCommandEvent& event)
{
	wxString strValue = m_pTxtX->GetValue();
	if(strValue.empty()) 
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.x = wxAtoi(strValue);
	m_pTxtX->Clear();
	strValue.Clear();

	strValue = m_pTxtY->GetValue();
	if(strValue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.y = wxAtoi(strValue);
	m_pTxtY->Clear();
	strValue.Clear();

	strValue = m_pTxtWidth->GetValue();
	if(strValue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.width = wxAtoi(strValue);
	m_pTxtWidth->Clear();
	strValue.Clear();
	
	strValue = m_pTxtHeight->GetValue();
	if(strValue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.pieceRect.height = wxAtoi(strValue);
	m_pTxtHeight->Clear();
	strValue.Clear();

	strValue = m_pTxtImageId->GetValue();
	if(strValue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.nImageId = wxAtoi(strValue);
	m_pTxtImageId->Clear();
	strValue.Clear();

	strValue = m_pTxtPieceId->GetValue();
	if(strValue.empty())
	{
		EndModal(wxCANCEL);
		return;
	}
	m_PieceInfo.strId = strValue;
	m_pTxtPieceId->Clear();
	strValue.Clear();

	EndModal(wxID_OK);
}

UIImagePieceDocument::PIECE_INFO DialogAddPiece::GetValue() 
{
	return m_PieceInfo;
}
