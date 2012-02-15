/*!
 * \file PieceListTransformer.cpp
 * \date 2-14-2012 1:25:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PieceListTransformer.h"
#include "../document/ImagePieceDocument.h"

PieceListTransformer::PieceListTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
}

PieceListTransformer::~PieceListTransformer()
{
	// TODO: 
}

PieceListTransformer& PieceListTransformer::GetInstance()
{
	static PieceListTransformer s_ImagePieceListTransformer;
	return s_ImagePieceListTransformer;
}

bool PieceListTransformer::Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid)
{
	m_pListView = pTreeCtrl;
	m_pPropertyGrid = pPropertyGrid;
	return true;
}

void PieceListTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("PieceList"));

	ImagePieceDocument::TM_PIECE_INFO& pieceInfoMap = ImagePieceDocument::GetInstance().GetPieceInfoMap();
	for (ImagePieceDocument::TM_PIECE_INFO::iterator it = pieceInfoMap.begin(); it != pieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pPieceInfo->GetId());
		pPieceInfo->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

void PieceListTransformer::UpdateProperty(PieceInfo* pPieceInfo)
{
	m_pPropertyGrid->Clear();
	if (!pPieceInfo) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pPieceInfo->GetId()));
	m_pPropertyGrid->Append(new wxStringProperty("image_id", "image_id", pPieceInfo->GetImageInfo()->GetId()))->Enable(false);

	m_pPropertyGrid->Append(new wxPropertyCategory("position", "position"));
	m_pPropertyGrid->Append(new wxIntProperty("x", "x", pPieceInfo->GetRect().x))->Enable(false);
	m_pPropertyGrid->Append(new wxIntProperty("y", "y", pPieceInfo->GetRect().y))->Enable(false);

	m_pPropertyGrid->Append(new wxPropertyCategory("size", "size"));
	m_pPropertyGrid->Append(new wxIntProperty("width", "width", pPieceInfo->GetRect().width))->Enable(false);
	m_pPropertyGrid->Append(new wxIntProperty("height", "height", pPieceInfo->GetRect().height))->Enable(false);
}

void PieceListTransformer::SetSelectedPieceInfo(PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return;

	m_pListView->SelectItem(pPieceInfo->GetTreeItemId(), true);
}

PieceInfo* PieceListTransformer::GetSelectedPieceInfo()
{
	wxString strPieceId = m_pListView->GetItemText(m_pListView->GetSelection());
	PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(strPieceId);
	return pPieceInfo;
}
