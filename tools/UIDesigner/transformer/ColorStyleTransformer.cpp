/*!
 * \file ColorStyleTransformer.cpp
 * \date 2-14-2012 17:01:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ColorStyleTransformer.h"
#include "../document/ColorStyleDocument.h"

ColorStyleTransformer::ColorStyleTransformer()
{
	m_pListView = NULL;
}

ColorStyleTransformer::~ColorStyleTransformer()
{
	// TODO: 
}

ColorStyleTransformer& ColorStyleTransformer::GetInstance()
{
	static ColorStyleTransformer s_ColorStyleTransformer;
	return s_ColorStyleTransformer;
}

bool ColorStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl)
{
	m_pListView = pTreeCtrl;
	return true;
}

void ColorStyleTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("ColorStyleList"));

	ColorStyleDocument::TM_COLOR_STYLE& ColorStyleMap = ColorStyleDocument::GetInstance().GetColorStyleMap();
	for (ColorStyleDocument::TM_COLOR_STYLE::iterator it = ColorStyleMap.begin(); it != ColorStyleMap.end(); ++it)
	{
		ColorStyle* pColorStyle = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pColorStyle->GetId());
		pColorStyle->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

ColorStyle* ColorStyleTransformer::GetSelectedColorStyle()
{
	wxString strColorStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	ColorStyle* pColorStyle = ColorStyleDocument::GetInstance().FindColorStyle(strColorStyleId);
	return pColorStyle;
}

void ColorStyleTransformer::SetSelectedColorStyle(ColorStyle* pColorStyle)
{
	if (pColorStyle)
	{
		m_pListView->SelectItem(pColorStyle->GetTreeItemId(), true);
	}
}
