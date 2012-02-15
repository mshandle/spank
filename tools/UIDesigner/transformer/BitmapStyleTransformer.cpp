/*!
 * \file BitmapStyleTransformer.cpp
 * \date 2-14-2012 14:46:38
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapStyleTransformer.h"
#include "../document/BitmapStyleDocument.h"
#include "../document/ImagePieceDocument.h"

BitmapStyleTransformer::BitmapStyleTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
}

BitmapStyleTransformer::~BitmapStyleTransformer()
{
	// TODO: 
}

BitmapStyleTransformer& BitmapStyleTransformer::GetInstance()
{
	static BitmapStyleTransformer s_BitmapStyleTransformer;
	return s_BitmapStyleTransformer;
}

bool BitmapStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid)
{
	m_pListView = pTreeCtrl;
	m_pPropertyGrid = pPropertyGrid;
	return true;
}

void BitmapStyleTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("BitmapStyleList"));

	BitmapStyleDocument::TM_BITMAP_STYLE& BitmapStyleMap = BitmapStyleDocument::GetInstance().GetBitmapStyleMap();
	for (BitmapStyleDocument::TM_BITMAP_STYLE::iterator it = BitmapStyleMap.begin(); it != BitmapStyleMap.end(); ++it)
	{
		BitmapStyle* pBitmapStyle = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pBitmapStyle->GetId());
		pBitmapStyle->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

void BitmapStyleTransformer::UpdateProperty(BitmapStyle* pBitmapStyle)
{
	m_pPropertyGrid->Clear();
	if (!pBitmapStyle) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pBitmapStyle->GetId()));

	const wxArrayString& pieceIds = ImagePieceDocument::GetInstance().GetPieceIds();
	const wxArrayInt& pieceIdsIndex = ImagePieceDocument::GetInstance().GetPieceIdsIndex();
	int value = -1;

	value = ImagePieceDocument::GetInstance().FindPieceIndex(pBitmapStyle->GetStatePiece(IStyle::SS_NORMAL)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("normal", "normal", pieceIds, pieceIdsIndex, value));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pBitmapStyle->GetStatePiece(IStyle::SS_DOWN)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("down", "down", pieceIds, pieceIdsIndex, value));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pBitmapStyle->GetStatePiece(IStyle::SS_HOVER)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("hover", "hover", pieceIds, pieceIdsIndex, value));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pBitmapStyle->GetStatePiece(IStyle::SS_DISABLED)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("disabled", "disabled", pieceIds, pieceIdsIndex, value));
}

void BitmapStyleTransformer::SetSelectedBitmapStyle(BitmapStyle* pBitmapStyle)
{
	if (!pBitmapStyle) return;

	m_pListView->SelectItem(pBitmapStyle->GetTreeItemId(), true);
}

BitmapStyle* BitmapStyleTransformer::GetSelectedBitmapStyle()
{
	wxString strBitmapStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	BitmapStyle* pBitmapStyle = BitmapStyleDocument::GetInstance().FindBitmapStyle(strBitmapStyleId);
	return pBitmapStyle;
}
