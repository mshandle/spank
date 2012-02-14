/*!
 * \file NineGridStyleTransformer.cpp
 * \date 2-14-2012 16:08:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NineGridStyleTransformer.h"
#include "../document/NineGridStyleDocument.h"

NineGridStyleTransformer::NineGridStyleTransformer()
{
	m_pListView = NULL;
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

bool NineGridStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl)
{
	m_pListView = pTreeCtrl;
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

NineGridStyle* NineGridStyleTransformer::GetSelectedNineGridStyle()
{
	wxString strNineGridStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	NineGridStyle* pNineGridStyle = NineGridStyleDocument::GetInstance().FindNineGridStyle(strNineGridStyleId);
	return pNineGridStyle;
}

void NineGridStyleTransformer::SetSelectedNineGridStyle(NineGridStyle* pNineGrieStyle)
{
	if (pNineGrieStyle)
	{
		m_pListView->SelectItem(pNineGrieStyle->GetTreeItemId(), true);
	}
}
