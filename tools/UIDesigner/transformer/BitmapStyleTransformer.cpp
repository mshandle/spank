/*!
 * \file BitmapStyleTransformer.cpp
 * \date 2-14-2012 14:46:38
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapStyleTransformer.h"
#include "../document/BitmapStyleDocument.h"

BitmapStyleTransformer::BitmapStyleTransformer()
{
	m_pListView = NULL;
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

bool BitmapStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl)
{
	m_pListView = pTreeCtrl;
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

BitmapStyle* BitmapStyleTransformer::GetSelectedBitmapStyle()
{
	wxString strBitmapStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	BitmapStyle* pBitmapStyle = BitmapStyleDocument::GetInstance().FindBitmapStyle(strBitmapStyleId);
	return pBitmapStyle;
}

void BitmapStyleTransformer::SetSelectedBitmapStyle(BitmapStyle* pBitmapStyle)
{
	if (pBitmapStyle)
	{
		m_pListView->SelectItem(pBitmapStyle->GetTreeItemId(), true);
	}
}
