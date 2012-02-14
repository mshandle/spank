/*!
 * \file ClipClipBitmapStyleTransformer.cpp
 * \date 2-14-2012 17:05:44
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ClipBitmapStyleTransformer.h"
#include "../document/ClipBitmapStyleDocument.h"

ClipBitmapStyleTransformer::ClipBitmapStyleTransformer()
{
	m_pListView = NULL;
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

bool ClipBitmapStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl)
{
	m_pListView = pTreeCtrl;
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

ClipBitmapStyle* ClipBitmapStyleTransformer::GetSelectedBitmapStyle()
{
	wxString strClipBitmapStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	ClipBitmapStyle* pClipBitmapStyle = ClipBitmapStyleDocument::GetInstance().FindClipBitmapStyle(strClipBitmapStyleId);
	return pClipBitmapStyle;
}

void ClipBitmapStyleTransformer::SetSelectedBitmapStyle(ClipBitmapStyle* pClipBitmapStyle)
{
	if (pClipBitmapStyle)
	{
		m_pListView->SelectItem(pClipBitmapStyle->GetTreeItemId(), true);
	}
}
