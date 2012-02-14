/*!
 * \file ColorStyle.cpp
 * \date 2-14-2012 16:23:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ColorStyle.h"

ColorStyle::ColorStyle()
{
	memset(m_nColors, 0, sizeof(m_nColors));
}

ColorStyle::~ColorStyle()
{
	// TODO: 
}

bool ColorStyle::LoadFromXml(TiXmlElement* pElmColorStyle)
{
	if (!pElmColorStyle) return false;

	wxString strId = pElmColorStyle->Attribute("id");
	SetId(strId);

	m_nColors[SS_NORMAL] = LoadStateInfo(pElmColorStyle, "normal", 0x808080);
	m_nColors[SS_DOWN] = LoadStateInfo(pElmColorStyle, "down", m_nColors[SS_NORMAL]);
	m_nColors[SS_HOVER] = LoadStateInfo(pElmColorStyle, "hover", m_nColors[SS_NORMAL]);
	m_nColors[SS_DISABLED] = LoadStateInfo(pElmColorStyle, "disabled", m_nColors[SS_NORMAL]);

	return true;
}

bool ColorStyle::SaveToXml(TiXmlElement* pElmColorStyleList)
{
	if (!pElmColorStyleList) return false;

	TiXmlElement* pElmColorStyle = new TiXmlElement("ColorStyle");
	pElmColorStyle->SetAttribute("id", GetId());

	if (!SaveStateInfo(pElmColorStyle, "normal", m_nColors[SS_NORMAL], true))
	{
		delete pElmColorStyle;
		pElmColorStyle = NULL;
		return false;
	}

	SaveStateInfo(pElmColorStyle, "down", m_nColors[SS_DOWN]);
	SaveStateInfo(pElmColorStyle, "hover", m_nColors[SS_HOVER]);
	SaveStateInfo(pElmColorStyle, "disabled", m_nColors[SS_DISABLED]);

	pElmColorStyleList->LinkEndChild(pElmColorStyle);
	return true;
}

unsigned int ColorStyle::LoadStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, unsigned int nDefaultColor)
{
	TiXmlElement* pElmState = pElmBitmapStyle->FirstChildElement(strState);
	if (!pElmState) return nDefaultColor;

	const char* pszColor = pElmState->Attribute("value");
	if (!pszColor) return nDefaultColor;

	unsigned int nColor = 0;
	sscanf_s(pszColor, "%x", &nColor);

	return nColor;
}

bool ColorStyle::SaveStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, unsigned int nColor, bool force /*= false*/)
{
	if (!force && nColor == m_nColors[SS_NORMAL]) return false;

	TiXmlElement* pElmState = new TiXmlElement(strState);

	char buff[128];
	sprintf_s(buff, "0x%X", nColor);

	pElmState->SetAttribute("value", buff);
	pElmBitmapStyle->LinkEndChild(pElmState);

	return true;
}
