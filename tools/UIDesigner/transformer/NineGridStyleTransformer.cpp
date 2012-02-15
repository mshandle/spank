/*!
 * \file NineGridStyleTransformer.cpp
 * \date 2-14-2012 16:08:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NineGridStyleTransformer.h"
#include "../document/NineGridStyleDocument.h"
#include "../document/ImagePieceDocument.h"

NineGridStyleTransformer::NineGridStyleTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
}

NineGridStyleTransformer::~NineGridStyleTransformer()
{
	// TODO: 
}

NineGridStyleTransformer& NineGridStyleTransformer::GetInstance()
{
	static NineGridStyleTransformer s_NineGridStyleTransformer;
	return s_NineGridStyleTransformer;
}

bool NineGridStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid)
{
	m_pListView = pTreeCtrl;
	m_pPropertyGrid = pPropertyGrid;
	return true;
}

void NineGridStyleTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("NineGridStyleList"));

	NineGridStyleDocument::TM_NINE_GRID_STYLE& NineGridStyleMap = NineGridStyleDocument::GetInstance().GetNineGridStyleMap();
	for (NineGridStyleDocument::TM_NINE_GRID_STYLE::iterator it = NineGridStyleMap.begin(); it != NineGridStyleMap.end(); ++it)
	{
		NineGridStyle* pNineGridStyle = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pNineGridStyle->GetId());
		pNineGridStyle->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

void NineGridStyleTransformer::SetSelectedNineGridStyle(NineGridStyle* pNineGrieStyle)
{
	if (!pNineGrieStyle) return;

	m_pListView->SelectItem(pNineGrieStyle->GetTreeItemId(), true);
}

NineGridStyle* NineGridStyleTransformer::GetSelectedNineGridStyle()
{
	wxString strNineGridStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	NineGridStyle* pNineGridStyle = NineGridStyleDocument::GetInstance().FindNineGridStyle(strNineGridStyleId);
	return pNineGridStyle;
}

void NineGridStyleTransformer::UpdateProperty(NineGridStyle* pNineGrieStyle)
{
	m_pPropertyGrid->Clear();
	if (!pNineGrieStyle) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pNineGrieStyle->GetId()));

	const wxArrayString& pieceIds = ImagePieceDocument::GetInstance().GetPieceIds();
	const wxArrayInt& pieceIdsIndex = ImagePieceDocument::GetInstance().GetPieceIdsIndex();
	int value = -1;

	m_pPropertyGrid->Append(new wxPropertyCategory("normal", "normal"));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pNineGrieStyle->GetStateGridInfo(IStyle::SS_NORMAL)->pPieceInfo->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("piece_id", "normal_piece_id", pieceIds, pieceIdsIndex, value));
	m_pPropertyGrid->Append(new wxIntProperty("min_x", "normal_min_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_NORMAL)->min_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("min_y", "normal_min_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_NORMAL)->min_y))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_x", "normal_max_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_NORMAL)->max_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_y", "normal_max_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_NORMAL)->max_y))->SetEditor(wxPGEditor_SpinCtrl);

	m_pPropertyGrid->Append(new wxPropertyCategory("down", "down"));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pNineGrieStyle->GetStateGridInfo(IStyle::SS_DOWN)->pPieceInfo->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("piece_id", "down_piece_id", pieceIds, pieceIdsIndex, value));
	m_pPropertyGrid->Append(new wxIntProperty("min_x", "down_min_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DOWN)->min_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("min_y", "down_min_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DOWN)->min_y))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_x", "down_max_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DOWN)->max_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_y", "down_max_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DOWN)->max_y))->SetEditor(wxPGEditor_SpinCtrl);

	m_pPropertyGrid->Append(new wxPropertyCategory("hover", "hover"));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pNineGrieStyle->GetStateGridInfo(IStyle::SS_HOVER)->pPieceInfo->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("piece_id", "hover_piece_id", pieceIds, pieceIdsIndex, value));
	m_pPropertyGrid->Append(new wxIntProperty("min_x", "hover_min_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_HOVER)->min_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("min_y", "hover_min_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_HOVER)->min_y))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_x", "hover_max_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_HOVER)->max_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_y", "hover_max_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_HOVER)->max_y))->SetEditor(wxPGEditor_SpinCtrl);

	m_pPropertyGrid->Append(new wxPropertyCategory("disabled", "disabled"));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pNineGrieStyle->GetStateGridInfo(IStyle::SS_DISABLED)->pPieceInfo->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("piece_id", "disabled_piece_id", pieceIds, pieceIdsIndex, value));
	m_pPropertyGrid->Append(new wxIntProperty("min_x", "disabled_min_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DISABLED)->min_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("min_y", "disabled_min_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DISABLED)->min_y))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_x", "disabled_max_x", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DISABLED)->max_x))->SetEditor(wxPGEditor_SpinCtrl);
	m_pPropertyGrid->Append(new wxIntProperty("max_y", "disabled_max_y", pNineGrieStyle->GetStateGridInfo(IStyle::SS_DISABLED)->max_y))->SetEditor(wxPGEditor_SpinCtrl);
}
