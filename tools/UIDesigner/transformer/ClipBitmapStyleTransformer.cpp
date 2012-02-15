/*!
 * \file ClipClipBitmapStyleTransformer.cpp
 * \date 2-14-2012 17:05:44
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ClipBitmapStyleTransformer.h"
#include "../document/ClipBitmapStyleDocument.h"
#include "../document/ImagePieceDocument.h"

ClipBitmapStyleTransformer::ClipBitmapStyleTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
}

ClipBitmapStyleTransformer::~ClipBitmapStyleTransformer()
{
	// TODO: 
}

ClipBitmapStyleTransformer& ClipBitmapStyleTransformer::GetInstance()
{
	static ClipBitmapStyleTransformer s_ClipBitmapStyleTransformer;
	return s_ClipBitmapStyleTransformer;
}

bool ClipBitmapStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid)
{
	m_pListView = pTreeCtrl;
	m_pPropertyGrid = pPropertyGrid;
	return true;
}

void ClipBitmapStyleTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("ClipBitmapStyleList"));

	ClipBitmapStyleDocument::TM_CLIP_BITMAP_STYLE& ClipBitmapStyleMap = ClipBitmapStyleDocument::GetInstance().GetClipBitmapStyleMap();
	for (ClipBitmapStyleDocument::TM_CLIP_BITMAP_STYLE::iterator it = ClipBitmapStyleMap.begin(); it != ClipBitmapStyleMap.end(); ++it)
	{
		ClipBitmapStyle* pClipBitmapStyle = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pClipBitmapStyle->GetId());
		pClipBitmapStyle->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

void ClipBitmapStyleTransformer::UpdateProperty(ClipBitmapStyle* pClipBitmapStyle)
{
	m_pPropertyGrid->Clear();
	if (!pClipBitmapStyle) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pClipBitmapStyle->GetId()));

	const wxArrayString& pieceIds = ImagePieceDocument::GetInstance().GetPieceIds();
	const wxArrayInt& pieceIdsIndex = ImagePieceDocument::GetInstance().GetPieceIdsIndex();
	int value = -1;

	value = ImagePieceDocument::GetInstance().FindPieceIndex(pClipBitmapStyle->GetStatePiece(IStyle::SS_NORMAL)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("normal", "normal", pieceIds, pieceIdsIndex, value));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pClipBitmapStyle->GetStatePiece(IStyle::SS_DOWN)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("down", "down", pieceIds, pieceIdsIndex, value));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pClipBitmapStyle->GetStatePiece(IStyle::SS_HOVER)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("hover", "hover", pieceIds, pieceIdsIndex, value));
	value = ImagePieceDocument::GetInstance().FindPieceIndex(pClipBitmapStyle->GetStatePiece(IStyle::SS_DISABLED)->GetId());
	m_pPropertyGrid->Append(new wxEnumProperty("disabled", "disabled", pieceIds, pieceIdsIndex, value));
}

void ClipBitmapStyleTransformer::SetSelectedClipBitmapStyle(ClipBitmapStyle* pClipBitmapStyle)
{
	if (!pClipBitmapStyle) return;

	m_pListView->SelectItem(pClipBitmapStyle->GetTreeItemId(), true);
}

ClipBitmapStyle* ClipBitmapStyleTransformer::GetSelectedClipBitmapStyle()
{
	wxString strClipBitmapStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	ClipBitmapStyle* pClipBitmapStyle = ClipBitmapStyleDocument::GetInstance().FindClipBitmapStyle(strClipBitmapStyleId);
	return pClipBitmapStyle;
}
