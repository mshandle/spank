/*!
 * \file ColorStyleDocument.cpp
 * \date 2-14-2012 16:55:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ColorStyleDocument.h"
#include <tinyxml-2.6.2/tinyxml.h>
#include <wx/msgdlg.h>
#include "../DesignerFrame.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

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
	SetFilePath(strFile);

	TiXmlElement* pElmColorStyleList = doc.RootElement();
	if (!pElmColorStyleList || strcmp(pElmColorStyleList->Value(), "ColorStyleList") != 0) return false;

	// parse image list
	TiXmlElement* pElmColorStyle = pElmColorStyleList->FirstChildElement("ColorStyle");
	while (pElmColorStyle)
	{
		ColorStyle* pColorStyle = new ColorStyle();
		if (!pColorStyle->LoadFromXml(pElmColorStyle))
		{
			wxMessageDialog msg(&DesignerFrame::GetInstance(), wxString::Format("load color style failed, id=%s", pColorStyle->GetId()));
			msg.ShowModal();
			SAFE_DELETE(pColorStyle);
		}
		else
		{
			m_ColorStyleMap.insert(std::make_pair(pColorStyle->GetId(), pColorStyle));
		}
		pElmColorStyle = pElmColorStyle->NextSiblingElement("ColorStyle");
	}

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
		if (!pColorStyle->SaveToXml(pElmColorStyleList))
		{
			wxMessageDialog msg(&DesignerFrame::GetInstance(), wxString::Format("save color style failed, id=%s", pColorStyle->GetId()));
			msg.ShowModal();
		}
	}

	return doc.SaveFile(strFile);
}

void ColorStyleDocument::Reset()
{
	SetFilePath(wxEmptyString);
	for (TM_COLOR_STYLE::iterator it = m_ColorStyleMap.begin(); it != m_ColorStyleMap.end(); ++it)
	{
		ColorStyle* pColorStyle = it->second;
		SAFE_DELETE(pColorStyle);
	}
	m_ColorStyleMap.clear();
	ClearModifiedFlag();
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

const ColorStyle* ColorStyleDocument::AddColorStyle(const wxString& strId)
{
	if (strId.empty()) return NULL;
	SetModifiedFlag();

	wxString strNewId = GenerateNewColorStyleId(strId);
	ColorStyle* pNewColorStyle = new ColorStyle();
	pNewColorStyle->SetId(strNewId);
	m_ColorStyleMap.insert(std::make_pair(pNewColorStyle->GetId(), pNewColorStyle));

	return pNewColorStyle;
}

bool ColorStyleDocument::RemoveColorStyle(const wxString& strId)
{
	TM_COLOR_STYLE::iterator itfound = m_ColorStyleMap.find(strId);
	if (itfound == m_ColorStyleMap.end()) return false;
	SetModifiedFlag();

	ColorStyle* pFoundColorStyle = (itfound->second);
	m_ColorStyleMap.erase(itfound);

	SAFE_DELETE(pFoundColorStyle);
	return true;
}

ColorStyle* ColorStyleDocument::InternalFindColorStyle(const wxString& strId)
{
	TM_COLOR_STYLE::iterator itfound = m_ColorStyleMap.find(strId);
	if (itfound == m_ColorStyleMap.end()) return NULL;
	return itfound->second;
}

wxString ColorStyleDocument::GenerateNewColorStyleId(const wxString& strId)
{
	wxString strNewId = strId;
	int index = 0;

	while (FindColorStyle(strNewId))
	{
		strNewId = wxString::Format("%s%d", strId, index++);
	}

	return strNewId;
}
