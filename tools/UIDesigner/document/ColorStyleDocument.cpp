/*!
 * \file ColorStyleDocument.cpp
 * \date 2-14-2012 16:55:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ColorStyleDocument.h"
#include "../transformer/ColorStyleTransformer.h"
#include <tinyxml-2.6.2/tinyxml.h>

ColorStyleDocument::ColorStyleDocument()
{
	// TODO: 
}

ColorStyleDocument::~ColorStyleDocument()
{
	Reset();
}

ColorStyleDocument& ColorStyleDocument::GetInstance()
{
	static ColorStyleDocument s_ColorStyleDocument;
	return s_ColorStyleDocument;
}

bool ColorStyleDocument::OpenFile(const wxString& strFile)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(strFile)) return false;

	Reset();

	TiXmlElement* pElmColorStyleList = doc.RootElement();
	if (!pElmColorStyleList || strcmp(pElmColorStyleList->Value(), "ColorStyleList") != 0) return false;

	// parse image list
	TiXmlElement* pElmColorStyle = pElmColorStyleList->FirstChildElement("ColorStyle");
	while (pElmColorStyle)
	{
		ColorStyle* pColorStyle = new ColorStyle();
		if (!pColorStyle->LoadFromXml(pElmColorStyle)) return false;
		m_ColorStyleMap.insert(std::make_pair(pColorStyle->GetId(), pColorStyle));
		pElmColorStyle = pElmColorStyle->NextSiblingElement("ColorStyle");
	}

	m_strFile = strFile;

	ColorStyleTransformer::GetInstance().UpdateListView();
	return true;
}

bool ColorStyleDocument::SaveFile(const wxString& strFile)
{
	if (!isModified()) return true;
	ClearModifiedFlag();

	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmColorStyleList = new TiXmlElement("ColorStyleList");
	doc.LinkEndChild(pElmColorStyleList);

	for (TM_COLOR_STYLE::iterator it = m_ColorStyleMap.begin(); it != m_ColorStyleMap.end(); ++it)
	{
		ColorStyle* pColorStyle = it->second;
		pColorStyle->SaveToXml(pElmColorStyleList);
	}

	return doc.SaveFile(strFile);
}

void ColorStyleDocument::Reset()
{
	m_strFile = wxEmptyString;
	for (TM_COLOR_STYLE::iterator it = m_ColorStyleMap.begin(); it != m_ColorStyleMap.end(); ++it)
	{
		ColorStyle* pColorStyle = it->second;
		delete pColorStyle;
	}
	m_ColorStyleMap.clear();
	ClearModifiedFlag();
}

const wxString& ColorStyleDocument::GetFilePath() const
{
	return m_strFile;
}

const ColorStyle* ColorStyleDocument::FindColorStyle(const wxString& strId)
{
	return InternalFindColorStyle(strId);
}

const ColorStyleDocument::TM_COLOR_STYLE& ColorStyleDocument::GetColorStyleMap()
{
	return m_ColorStyleMap;
}

bool ColorStyleDocument::RenameColorStyleId(const ColorStyle* pColorStyle, const wxString& strNewId)
{
	if (!pColorStyle) return false;

	wxString strOldId = pColorStyle->GetId();
	if (strOldId == strNewId) return true;
	if (FindColorStyle(strNewId)) return false;

	TM_COLOR_STYLE::iterator itfound = m_ColorStyleMap.find(strOldId);
	if (itfound == m_ColorStyleMap.end()) return false;
	SetModifiedFlag();

	ColorStyle* pFoundColorStyle = itfound->second;
	m_ColorStyleMap.erase(itfound);

	pFoundColorStyle->SetId(strNewId);
	m_ColorStyleMap.insert(std::make_pair(pFoundColorStyle->GetId(), pFoundColorStyle));

	ColorStyleTransformer::GetInstance().UpdateListView();
	ColorStyleTransformer::GetInstance().SetSelectedColorStyle(pFoundColorStyle);
	return true;
}

bool ColorStyleDocument::SetStateColor(const ColorStyle* pColorStyle, const wxColour& color, IStyle::STYLE_STATE eState)
{
	if (!pColorStyle) return false;

	ColorStyle* pFoundColorStyle = InternalFindColorStyle(pColorStyle->GetId());
	if (!pFoundColorStyle) return false;
	SetModifiedFlag();

	return pFoundColorStyle->SetStateColor(color.GetRGB(), eState);
}

ColorStyle* ColorStyleDocument::InternalFindColorStyle(const wxString& strId)
{
	TM_COLOR_STYLE::iterator itfound = m_ColorStyleMap.find(strId);
	if (itfound == m_ColorStyleMap.end()) return NULL;
	return itfound->second;
}