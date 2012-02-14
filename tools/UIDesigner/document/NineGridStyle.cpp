/*!
 * \file NineGridStyle.cpp
 * \date 2-14-2012 15:16:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NineGridStyle.h"
#include "ImagePieceDocument.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

NineGridStyle::NineGridStyle()
{
	memset(m_NineGridInfo, 0, sizeof(m_NineGridInfo));
}

NineGridStyle::~NineGridStyle()
{
	Clear();
}

bool NineGridStyle::LoadFromXml(TiXmlElement* pElmNineGridStyle)
{
	if (!pElmNineGridStyle) return false;

	wxString strId = pElmNineGridStyle->Attribute("id");
	SetId(strId);

	Clear();

	m_NineGridInfo[SS_NORMAL] = LoadStateInfo(pElmNineGridStyle, "normal", NULL);
	if (!m_NineGridInfo[SS_NORMAL]) return false;

	m_NineGridInfo[SS_DOWN] = LoadStateInfo(pElmNineGridStyle, "down", m_NineGridInfo[SS_NORMAL]);
	m_NineGridInfo[SS_HOVER] = LoadStateInfo(pElmNineGridStyle, "hover", m_NineGridInfo[SS_NORMAL]);
	m_NineGridInfo[SS_DISABLED] = LoadStateInfo(pElmNineGridStyle, "disabled", m_NineGridInfo[SS_NORMAL]);

	return true;
}

bool NineGridStyle::SaveToXml(TiXmlElement* pElmBitmapStyleList)
{
	if (!pElmBitmapStyleList) return false;

	TiXmlElement* pElmBitmapStyle = new TiXmlElement("BitmapStyle");
	pElmBitmapStyle->SetAttribute("id", GetId());

	if (!SaveStateInfo(pElmBitmapStyle, "normal", m_NineGridInfo[SS_NORMAL], true))
	{
		delete pElmBitmapStyle;
		pElmBitmapStyle = NULL;
		return false;
	}

	SaveStateInfo(pElmBitmapStyle, "down", m_NineGridInfo[SS_DOWN]);
	SaveStateInfo(pElmBitmapStyle, "hover", m_NineGridInfo[SS_HOVER]);
	SaveStateInfo(pElmBitmapStyle, "disabled", m_NineGridInfo[SS_DISABLED]);

	pElmBitmapStyleList->LinkEndChild(pElmBitmapStyle);
	return true;
}

NineGridStyle::NINE_GRID_INFO* NineGridStyle::LoadStateInfo(TiXmlElement* pElmNineGridStyle, const wxString& strState, NINE_GRID_INFO* pDefaultInfo)
{
	TiXmlElement* pElmState = pElmNineGridStyle->FirstChildElement(strState);
	if (!pElmState) return pDefaultInfo;

	const char* pszPieceId = pElmState->Attribute("piece_id");
	if (!pszPieceId) return pDefaultInfo;

	PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(pszPieceId);
	if (!pPieceInfo) return pDefaultInfo;

	NINE_GRID_INFO* pNineGridInfo = new NINE_GRID_INFO();
	pNineGridInfo->pPieceInfo = pPieceInfo;
	pElmState->Attribute("min_x", &pNineGridInfo->min_x);
	pElmState->Attribute("min_y", &pNineGridInfo->min_y);
	pElmState->Attribute("max_x", &pNineGridInfo->max_x);
	pElmState->Attribute("max_y", &pNineGridInfo->max_y);

	return pNineGridInfo;
}

bool NineGridStyle::SaveStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, NINE_GRID_INFO* pNineGridInfo, bool force /*= false*/)
{
	if (!pNineGridInfo) return false;
	if (!force && pNineGridInfo == m_NineGridInfo[SS_NORMAL]) return false;

	TiXmlElement* pElmState = new TiXmlElement(strState);
	pElmState->SetAttribute("piece_id", pNineGridInfo->pPieceInfo->GetId());
	pElmState->SetAttribute("min_x", pNineGridInfo->min_x);
	pElmState->SetAttribute("min_y", pNineGridInfo->min_y);
	pElmState->SetAttribute("max_x", pNineGridInfo->max_x);
	pElmState->SetAttribute("max_y", pNineGridInfo->max_y);

	pElmBitmapStyle->LinkEndChild(pElmState);

	return true;
}

void NineGridStyle::Clear()
{
	if (m_NineGridInfo[SS_DISABLED] != m_NineGridInfo[SS_NORMAL]) SAFE_DELETE(m_NineGridInfo[SS_DISABLED]);
	if (m_NineGridInfo[SS_HOVER] != m_NineGridInfo[SS_NORMAL]) SAFE_DELETE(m_NineGridInfo[SS_HOVER]);
	if (m_NineGridInfo[SS_DOWN] != m_NineGridInfo[SS_NORMAL]) SAFE_DELETE(m_NineGridInfo[SS_DOWN]);
	SAFE_DELETE(m_NineGridInfo[SS_NORMAL]);
}
