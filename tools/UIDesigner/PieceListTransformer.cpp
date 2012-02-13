/*!
 * \file PieceListTransformer.cpp
 * \date 2-14-2012 1:25:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PieceListTransformer.h"
#include "ImagePieceDocument.h"

PieceListTransformer::PieceListTransformer()
{
	m_pListView = NULL;
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

bool PieceListTransformer::Initialize(wxTreeCtrl* pTreeCtrl)
{
	m_pListView = pTreeCtrl;
	return true;
}

void PieceListTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("ImagePiece"));

	ImagePieceDocument::TM_PIECE_INFO& pieceInfoMap = ImagePieceDocument::GetInstance().GetPieceInfoMap();
	for (ImagePieceDocument::TM_PIECE_INFO::iterator it = pieceInfoMap.begin(); it != pieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pPieceInfo->GetId());
		pPieceInfo->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();

	wxTreeItemIdValue value;
	if(pieceInfoMap.empty()) return;
	m_pListView->SelectItem(m_pListView->GetFirstChild(rootItem, value));
}

PieceInfo* PieceListTransformer::GetSelectedPieceInfo()
{
	wxString strPieceId = m_pListView->GetItemText(m_pListView->GetSelection());
	PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(strPieceId);
	return pPieceInfo;
}
