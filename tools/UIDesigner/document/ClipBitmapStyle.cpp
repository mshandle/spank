/*!
 * \file ClipBitmapStyle.cpp
 * \date 2-14-2012 16:44:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ClipBitmapStyle.h"
#include "ImagePieceDocument.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

ClipBitmapStyle::ClipBitmapStyle()
{
	memset(m_PieceInfo, 0, sizeof(m_PieceInfo));
}

ClipBitmapStyle::~ClipBitmapStyle()
{
	// TODO: 
}

bool ClipBitmapStyle::LoadFromXml(TiXmlElement* pElmClipBitmapStyle)
{
	if (!pElmClipBitmapStyle) return false;

	wxString strId = pElmClipBitmapStyle->Attribute("id");
	SetId(strId);

	m_PieceInfo[SS_NORMAL] = LoadStateInfo(pElmClipBitmapStyle, "normal", NULL);
	if (!m_PieceInfo[SS_NORMAL]) return false;

	m_PieceInfo[SS_DOWN] = LoadStateInfo(pElmClipBitmapStyle, "down", NULL);
	m_PieceInfo[SS_HOVER] = LoadStateInfo(pElmClipBitmapStyle, "hover", NULL);
	m_PieceInfo[SS_DISABLED] = LoadStateInfo(pElmClipBitmapStyle, "disabled", NULL);

	return true;
}

bool ClipBitmapStyle::SaveToXml(TiXmlElement* pElmClipBitmapStyleList)
{
	if (!pElmClipBitmapStyleList) return false;

	TiXmlElement* pElmClipBitmapStyle = new TiXmlElement("ClipBitmapStyle");
	pElmClipBitmapStyle->SetAttribute("id", GetId());

	if (!SaveStateInfo(pElmClipBitmapStyle, "normal", m_PieceInfo[SS_NORMAL]))
	{
		SAFE_DELETE(pElmClipBitmapStyle);
		return false;
	}

	if (m_PieceInfo[SS_NORMAL] != m_PieceInfo[SS_DOWN]) SaveStateInfo(pElmClipBitmapStyle, "down", m_PieceInfo[SS_DOWN]);
	if (m_PieceInfo[SS_NORMAL] != m_PieceInfo[SS_HOVER]) SaveStateInfo(pElmClipBitmapStyle, "hover", m_PieceInfo[SS_HOVER]);
	if (m_PieceInfo[SS_NORMAL] != m_PieceInfo[SS_DISABLED]) SaveStateInfo(pElmClipBitmapStyle, "disabled", m_PieceInfo[SS_DISABLED]);

	pElmClipBitmapStyleList->LinkEndChild(pElmClipBitmapStyle);
	return true;
}

bool ClipBitmapStyle::SetStatePiece(const PieceInfo* pPieceInfo, STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_PieceInfo[eState] == pPieceInfo) return false;
	m_PieceInfo[eState] = pPieceInfo;
	return true;
}

const PieceInfo* ClipBitmapStyle::GetStatePiece(STYLE_STATE eState) const
{
	if (eState < 0 || eState >= SS_NUM) return NULL;

	return m_PieceInfo[eState];
}

const PieceInfo* ClipBitmapStyle::LoadStateInfo(TiXmlElement* pElmClipBitmapStyle, const wxString& strState, const PieceInfo* pDefaultPieceInfo)
{
	TiXmlElement* pElmState = pElmClipBitmapStyle->FirstChildElement(strState);
	if (!pElmState) return pDefaultPieceInfo;

	const char* pszPieceId = pElmState->Attribute("piece_id");
	if (!pszPieceId) return pDefaultPieceInfo;

	const PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(pszPieceId);
	if (!pPieceInfo) return pDefaultPieceInfo;

	return pPieceInfo;
}

bool ClipBitmapStyle::SaveStateInfo(TiXmlElement* pElmClipBitmapStyle, const wxString& strState, const PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return false;

	TiXmlElement* pElmState = new TiXmlElement(strState);
	pElmState->SetAttribute("piece_id", pPieceInfo->GetId());
	pElmClipBitmapStyle->LinkEndChild(pElmState);

	return true;
}
