/*!
 * \file PieceListTransformer.cpp
 * \date 2-14-2012 1:25:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PieceListTransformer.h"
#include "../ImagePackerFrame.h"
#include "../document/ImagePieceDocument.h"

PieceListTransformer::PieceListTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
	m_bSkipUpdateProperty = false;
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

	const ImagePieceDocument::TM_PIECE_INFO& pieceInfoMap = ImagePieceDocument::GetInstance().GetPieceInfoMap();
	for (ImagePieceDocument::TM_PIECE_INFO::const_iterator it = pieceInfoMap.begin(); it != pieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pPieceInfo->GetId());
		((PieceInfo*)pPieceInfo)->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

void PieceListTransformer::UpdateProperty(const PieceInfo* pPieceInfo)
{
	if (m_bSkipUpdateProperty) return;

	m_pPropertyGrid->Clear();
	ImagePackerFrame::GetInstance().SetCurrPropertyType(ImagePackerFrame::PT_UNKNOWN);
	if (!pPieceInfo) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pPieceInfo->GetId()));
	m_pPropertyGrid->Append(new wxStringProperty("image_id", "image_id", pPieceInfo->GetImageInfo()->GetId()))->Enable(false);

	m_pPropertyGrid->Append(new wxPropertyCategory("position", "position"));
	m_pPropertyGrid->Append(new wxIntProperty("x", "x", pPieceInfo->GetRect().x))->Enable(false);
	m_pPropertyGrid->Append(new wxIntProperty("y", "y", pPieceInfo->GetRect().y))->Enable(false);

	m_pPropertyGrid->Append(new wxPropertyCategory("size", "size"));
	m_pPropertyGrid->Append(new wxIntProperty("width", "width", pPieceInfo->GetRect().width))->Enable(false);
	m_pPropertyGrid->Append(new wxIntProperty("height", "height", pPieceInfo->GetRect().height))->Enable(false);

	ImagePackerFrame::GetInstance().SetCurrPropertyType(ImagePackerFrame::PT_PIECE);
}

void PieceListTransformer::PropertyChanged(const wxPGProperty* pProperty)
{
	const PieceInfo* pPieceInfo = GetSelectedPieceInfo();
	if (!pPieceInfo) return;

	if (pProperty->GetName() == "id")
	{
		wxString strNewId = pProperty->GetValueAsString();
		if (ImagePieceDocument::GetInstance().RenamePieceInfoId(pPieceInfo, strNewId))
		{
			UpdateListView();
			m_bSkipUpdateProperty = true;
			SetSelectedPieceInfo(pPieceInfo);
			m_bSkipUpdateProperty = false;
		}
	}
}

void PieceListTransformer::SetSelectedPieceInfo(const PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return;

	m_pListView->SelectItem(pPieceInfo->GetTreeItemId(), true);
}

const PieceInfo* PieceListTransformer::GetSelectedPieceInfo()
{
	wxString strPieceId = m_pListView->GetItemText(m_pListView->GetSelection());
	const PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(strPieceId);
	return pPieceInfo;
}
