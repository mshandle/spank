/*!
 * \file ColorStyle.cpp
 * \date 2-14-2012 16:23:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ColorStyle.h"
#include "../Config.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

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

	m_nColors[SS_NORMAL] = LoadStateInfo(pElmColorStyle, "normal", Config::DEFAULT_COLOR);
	m_nColors[SS_DOWN] = LoadStateInfo(pElmColorStyle, "down", Config::DEFAULT_COLOR);
	m_nColors[SS_HOVER] = LoadStateInfo(pElmColorStyle, "hover", Config::DEFAULT_COLOR);
	m_nColors[SS_DISABLED] = LoadStateInfo(pElmColorStyle, "disabled", Config::DEFAULT_COLOR);

	return true;
}

bool ColorStyle::SaveToXml(TiXmlElement* pElmColorStyleList)
{
	if (!pElmColorStyleList) return false;

	TiXmlElement* pElmColorStyle = new TiXmlElement("ColorStyle");
	pElmColorStyle->SetAttribute("id", GetId());

	if (!SaveStateInfo(pElmColorStyle, "normal", m_nColors[SS_NORMAL]))
	{
		SAFE_DELETE(pElmColorStyle);
		return false;
	}

	if (m_nColors[SS_NORMAL] != m_nColors[SS_DOWN]) SaveStateInfo(pElmColorStyle, "down", m_nColors[SS_DOWN]);
	if (m_nColors[SS_NORMAL] != m_nColors[SS_HOVER]) SaveStateInfo(pElmColorStyle, "hover", m_nColors[SS_HOVER]);
	if (m_nColors[SS_NORMAL] != m_nColors[SS_DISABLED]) SaveStateInfo(pElmColorStyle, "disabled", m_nColors[SS_DISABLED]);

	pElmColorStyleList->LinkEndChild(pElmColorStyle);
	return true;
}

bool ColorStyle::SaveStateInfo(TiXmlElement* pElmColorStyle, const wxString& strState, unsigned int nColor)
{
	TiXmlElement* pElmState = new TiXmlElement(strState);

	char buff[128];
	sprintf_s(buff, "0x%X", nColor);

	pElmState->SetAttribute("value", buff);
	pElmColorStyle->LinkEndChild(pElmState);

	return true;
}

bool ColorStyle::SetStateColor(unsigned int color, STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_nColors[eState] == color) return false;
	m_nColors[eState] = color;
	return true;
}

unsigned int ColorStyle::GetStateColor(STYLE_STATE eState) const
{
	if (eState < 0 || eState >= SS_NUM) return Config::DEFAULT_COLOR;
	return m_nColors[eState];
}

unsigned int ColorStyle::LoadStateInfo(TiXmlElement* pElmColorStyle, const wxString& strState, unsigned int nDefaultColor)
{
	TiXmlElement* pElmState = pElmColorStyle->FirstChildElement(strState);
	if (!pElmState) return nDefaultColor;

	const char* pszColor = pElmState->Attribute("value");
	if (!pszColor) return nDefaultColor;

	unsigned int nColor = 0;
	sscanf_s(pszColor, "%x", &nColor);

	return nColor;
}
