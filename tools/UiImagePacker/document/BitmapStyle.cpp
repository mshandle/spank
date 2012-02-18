/*!
 * \file BitmapStyle.cpp
 * \date 2-14-2012 13:52:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapStyle.h"
#include "ImagePieceDocument.h"
#include <wx/msgdlg.h>
#include "../ImagePackerFrame.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

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

	m_PieceInfo[SS_DOWN] = LoadStateInfo(pElmBitmapStyle, "down", NULL);
	m_PieceInfo[SS_HOVER] = LoadStateInfo(pElmBitmapStyle, "hover", NULL);
	m_PieceInfo[SS_DISABLED] = LoadStateInfo(pElmBitmapStyle, "disabled", NULL);

	return true;
}

bool BitmapStyle::SaveToXml(TiXmlElement* pElmBitmapStyleList)
{
	if (!pElmBitmapStyleList) return false;

	TiXmlElement* pElmBitmapStyle = new TiXmlElement("BitmapStyle");
	pElmBitmapStyle->SetAttribute("id", GetId());

	if (!SaveStateInfo(pElmBitmapStyle, "normal", m_PieceInfo[SS_NORMAL]))
	{
		SAFE_DELETE(pElmBitmapStyle);
		return false;
	}

	if (m_PieceInfo[SS_NORMAL] != m_PieceInfo[SS_DOWN]) SaveStateInfo(pElmBitmapStyle, "down", m_PieceInfo[SS_DOWN]);
	if (m_PieceInfo[SS_NORMAL] != m_PieceInfo[SS_HOVER]) SaveStateInfo(pElmBitmapStyle, "hover", m_PieceInfo[SS_HOVER]);
	if (m_PieceInfo[SS_NORMAL] != m_PieceInfo[SS_DISABLED]) SaveStateInfo(pElmBitmapStyle, "disabled", m_PieceInfo[SS_DISABLED]);

	pElmBitmapStyleList->LinkEndChild(pElmBitmapStyle);
	return true;
}

bool BitmapStyle::SetStatePiece(const PieceInfo* pPieceInfo, STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_PieceInfo[eState] == pPieceInfo) return false;
	m_PieceInfo[eState] = pPieceInfo;
	return true;
}

const PieceInfo* BitmapStyle::GetStatePiece(STYLE_STATE eState) const
{
	if (eState < 0 || eState >= SS_NUM) return NULL;
	return m_PieceInfo[eState];
}

const PieceInfo* BitmapStyle::LoadStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, const PieceInfo* pDefaultPieceInfo)
{
	TiXmlElement* pElmState = pElmBitmapStyle->FirstChildElement(strState);
	if (!pElmState) return pDefaultPieceInfo;

	const char* pszPieceId = pElmState->Attribute("piece_id");
	if (!pszPieceId) return pDefaultPieceInfo;

	const PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(pszPieceId);
	if (!pPieceInfo)
	{
		wxMessageDialog msg(&ImagePackerFrame::GetInstance(), wxString::Format("can not found piece id=%s, for bitmap style id=%s", pszPieceId, GetId()));
		msg.ShowModal();
		return pDefaultPieceInfo;
	}

	return pPieceInfo;
}

bool BitmapStyle::SaveStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, const PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return false;

	TiXmlElement* pElmState = new TiXmlElement(strState);
	pElmState->SetAttribute("piece_id", pPieceInfo->GetId());
	pElmBitmapStyle->LinkEndChild(pElmState);

	return true;
}
