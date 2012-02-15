/*!
 * \file ColorStyleTransformer.cpp
 * \date 2-14-2012 17:01:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ColorStyleTransformer.h"
#include "../DesignerFrame.h"
#include "../document/ColorStyleDocument.h"
#include "../editor/ColorStyleEditor.h"

ColorStyleTransformer::ColorStyleTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
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

bool ColorStyleTransformer::Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid)
{
	m_pListView = pTreeCtrl;
	m_pPropertyGrid = pPropertyGrid;
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

void ColorStyleTransformer::UpdateProperty(ColorStyle* pColorStyle)
{
	m_pPropertyGrid->Clear();
	DesignerFrame::GetInstance().SetCurrPropertyType(DesignerFrame::PT_UNKNOWN);
	if (!pColorStyle) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pColorStyle->GetId()));

	wxColour color;

	color.SetRGB(pColorStyle->GetStateColor(IStyle::SS_NORMAL));
	m_pPropertyGrid->Append(new wxColourProperty("normal", "normal", color));
	color.SetRGB(pColorStyle->GetStateColor(IStyle::SS_DOWN));
	m_pPropertyGrid->Append(new wxColourProperty("down", "down", color));
	color.SetRGB(pColorStyle->GetStateColor(IStyle::SS_HOVER));
	m_pPropertyGrid->Append(new wxColourProperty("hover", "hover", color));
	color.SetRGB(pColorStyle->GetStateColor(IStyle::SS_DISABLED));
	m_pPropertyGrid->Append(new wxColourProperty("disabled", "disabled", color));

	DesignerFrame::GetInstance().SetCurrPropertyType(DesignerFrame::PT_COLOR_STYLE);
}

void ColorStyleTransformer::PropertyChanged(wxPGProperty* pProperty)
{
	ColorStyle* pColorStyle = GetSelectedColorStyle();
	if (!pColorStyle) return;

	bool bRedraw = false;
	if (pProperty->GetName() == "id")
	{
		wxString strNewId = pProperty->GetValueAsString();
		ColorStyleDocument::GetInstance().RenameColorStyleId(pColorStyle, strNewId);
	}
	else if (pProperty->GetName() == "normal")
	{
		wxColour color;
		color << pProperty->GetValue();
		bRedraw = ColorStyleDocument::GetInstance().SetStateColor(pColorStyle, color, IStyle::SS_NORMAL);
	}
	else if (pProperty->GetName() == "down")
	{
		wxColour color;
		color << pProperty->GetValue();
 		bRedraw = ColorStyleDocument::GetInstance().SetStateColor(pColorStyle, color, IStyle::SS_DOWN);
	}
	else if (pProperty->GetName() == "hover")
	{
		wxColour color;
		color << pProperty->GetValue();
		bRedraw = ColorStyleDocument::GetInstance().SetStateColor(pColorStyle, color, IStyle::SS_HOVER);
	}
	else if (pProperty->GetName() == "disabled")
	{
		wxColour color;
		color << pProperty->GetValue();
		bRedraw = ColorStyleDocument::GetInstance().SetStateColor(pColorStyle, color, IStyle::SS_DISABLED);
	}

	if (bRedraw)
	{
		ColorStyleEditor::GetInstance().SetColorStyle(NULL);
		ColorStyleEditor::GetInstance().SetColorStyle(pColorStyle);
	}
}

void ColorStyleTransformer::SetSelectedColorStyle(ColorStyle* pColorStyle)
{
	if (!pColorStyle) return;

	m_pListView->SelectItem(pColorStyle->GetTreeItemId(), true);
}

ColorStyle* ColorStyleTransformer::GetSelectedColorStyle()
{
	wxString strColorStyleId = m_pListView->GetItemText(m_pListView->GetSelection());
	ColorStyle* pColorStyle = ColorStyleDocument::GetInstance().FindColorStyle(strColorStyleId);
	return pColorStyle;
}
