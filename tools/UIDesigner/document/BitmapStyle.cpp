/*!
 * \file BitmapStyle.cpp
 * \date 2-14-2012 13:52:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapStyle.h"
#include "ImagePieceDocument.h"

BitmapStyle::BitmapStyle()
{
	memset(m_PieceInfo, 0, sizeof(m_PieceInfo));
}

BitmapStyle::~BitmapStyle()
{
	// TODO: 
}

bool BitmapStyle::LoadFromXml(TiXmlElement* pElmBitmapStyle)
{
	if (!pElmBitmapStyle) return false;

	wxString strId = pElmBitmapStyle->Attribute("id");
	SetId(strId);

	m_PieceInfo[SS_NORMAL] = LoadStateInfo(pElmBitmapStyle, "normal", NULL);
	if (!m_PieceInfo[SS_NORMAL]) return false;

	m_PieceInfo[SS_DOWN] = LoadStateInfo(pElmBitmapStyle, "down", m_PieceInfo[SS_NORMAL]);
	m_PieceInfo[SS_HOVER] = LoadStateInfo(pElmBitmapStyle, "hover", m_PieceInfo[SS_NORMAL]);
	m_PieceInfo[SS_DISABLED] = LoadStateInfo(pElmBitmapStyle, "disabled", m_PieceInfo[SS_NORMAL]);

	return true;
}

bool BitmapStyle::SaveToXml(TiXmlElement* pElmBitmapStyleList)
{
	if (!pElmBitmapStyleList) return false;

	TiXmlElement* pElmBitmapStyle = new TiXmlElement("BitmapStyle");
	pElmBitmapStyle->SetAttribute("id", GetId());

	if (!SaveStateInfo(pElmBitmapStyle, "normal", m_PieceInfo[SS_NORMAL], true))
	{
		delete pElmBitmapStyle;
		pElmBitmapStyle = NULL;
		return false;
	}

	SaveStateInfo(pElmBitmapStyle, "down", m_PieceInfo[SS_DOWN]);
	SaveStateInfo(pElmBitmapStyle, "hover", m_PieceInfo[SS_HOVER]);
	SaveStateInfo(pElmBitmapStyle, "disabled", m_PieceInfo[SS_DISABLED]);

	pElmBitmapStyleList->LinkEndChild(pElmBitmapStyle);
	return true;
}

PieceInfo* BitmapStyle::GetStatePiece(STYLE_STATE eState)
{
	return m_PieceInfo[eState];
}

PieceInfo* BitmapStyle::LoadStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, PieceInfo* defaultPieceInfo)
{
	TiXmlElement* pElmState = pElmBitmapStyle->FirstChildElement(strState);
	if (!pElmState) return defaultPieceInfo;

	const char* pszPieceId = pElmState->Attribute("piece_id");
	if (!pszPieceId) return defaultPieceInfo;

	PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(pszPieceId);
	if (!pPieceInfo) return defaultPieceInfo;

	return pPieceInfo;
}

bool BitmapStyle::SaveStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, PieceInfo* pPieceInfo, bool force /*= false*/)
{
	if (!pPieceInfo) return false;
	if (!force && pPieceInfo == m_PieceInfo[SS_NORMAL]) return false;

	TiXmlElement* pElmState = new TiXmlElement(strState);
	pElmState->SetAttribute("piece_id", pPieceInfo->GetId());
	pElmBitmapStyle->LinkEndChild(pElmState);

	return true;
}