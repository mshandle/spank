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
	// TODO: 
}

bool NineGridStyle::LoadFromXml(TiXmlElement* pElmNineGridStyle)
{
	if (!pElmNineGridStyle) return false;

	wxString strId = pElmNineGridStyle->Attribute("id");
	SetId(strId);

	if (!LoadStateInfo(m_NineGridInfo[SS_NORMAL], pElmNineGridStyle, "normal")) return false;
	if (!LoadStateInfo(m_NineGridInfo[SS_DOWN], pElmNineGridStyle, "down")) m_NineGridInfo[SS_DOWN] = m_NineGridInfo[SS_NORMAL];
	if (!LoadStateInfo(m_NineGridInfo[SS_HOVER], pElmNineGridStyle, "hover")) m_NineGridInfo[SS_HOVER] = m_NineGridInfo[SS_NORMAL];
	if (!LoadStateInfo(m_NineGridInfo[SS_DISABLED], pElmNineGridStyle, "disabled")) m_NineGridInfo[SS_DISABLED] = m_NineGridInfo[SS_NORMAL];

	return true;
}

bool NineGridStyle::SaveToXml(TiXmlElement* pElmBitmapStyleList)
{
	if (!pElmBitmapStyleList) return false;

	TiXmlElement* pElmBitmapStyle = new TiXmlElement("NineGridStyle");
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

bool NineGridStyle::SetStatePiece(PieceInfo* pPieceInfo, STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_NineGridInfo[eState].pPieceInfo == pPieceInfo) return false;
	if (!pPieceInfo && m_NineGridInfo[eState].pPieceInfo == m_NineGridInfo[SS_NORMAL].pPieceInfo) return false;

	m_NineGridInfo[eState].pPieceInfo = pPieceInfo;
	return true;
}

NineGridStyle::NINE_GRID_INFO* NineGridStyle::GetStateGridInfo(STYLE_STATE eState)
{
	return &m_NineGridInfo[eState];
}

bool NineGridStyle::LoadStateInfo(NINE_GRID_INFO& NineGridInfoOut, TiXmlElement* pElmNineGridStyle, const wxString& strState)
{
	TiXmlElement* pElmState = pElmNineGridStyle->FirstChildElement(strState);
	if (!pElmState) return false;

	const char* pszPieceId = pElmState->Attribute("piece_id");
	if (!pszPieceId) return false;

	PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(pszPieceId);
	if (!pPieceInfo) return false;

	NineGridInfoOut.pPieceInfo = pPieceInfo;
	pElmState->Attribute("min_x", &NineGridInfoOut.min_x);
	pElmState->Attribute("min_y", &NineGridInfoOut.min_y);
	pElmState->Attribute("max_x", &NineGridInfoOut.max_x);
	pElmState->Attribute("max_y", &NineGridInfoOut.max_y);

	return true;
}

bool NineGridStyle::SaveStateInfo(TiXmlElement* pElmNineGridStyle, const wxString& strState, const NINE_GRID_INFO& NineGridInfo, bool force /* = false */)
{
	if (!force && IsNormalGrid(NineGridInfo)) return false;

	TiXmlElement* pElmState = new TiXmlElement(strState);
	pElmState->SetAttribute("piece_id", NineGridInfo.pPieceInfo->GetId());
	pElmState->SetAttribute("min_x", NineGridInfo.min_x);
	pElmState->SetAttribute("min_y", NineGridInfo.min_y);
	pElmState->SetAttribute("max_x", NineGridInfo.max_x);
	pElmState->SetAttribute("max_y", NineGridInfo.max_y);

	pElmNineGridStyle->LinkEndChild(pElmState);

	return true;
}

bool NineGridStyle::IsNormalGrid(const NINE_GRID_INFO& NineGridInfo)
{
	if (NineGridInfo.min_x != m_NineGridInfo[SS_NORMAL].min_x) return false;
	if (NineGridInfo.min_y != m_NineGridInfo[SS_NORMAL].min_y) return false;
	if (NineGridInfo.max_x != m_NineGridInfo[SS_NORMAL].max_x) return false;
	if (NineGridInfo.max_y != m_NineGridInfo[SS_NORMAL].max_y) return false;
	if (NineGridInfo.pPieceInfo != m_NineGridInfo[SS_NORMAL].pPieceInfo) return false;
	return true;
}

bool NineGridStyle::SetStateMinX(int value, IStyle::STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_NineGridInfo[eState].min_x == value) return false;

	m_NineGridInfo[eState].min_x = value;
	if (m_NineGridInfo[eState].min_x == m_NineGridInfo[eState].max_x)
	{
		m_NineGridInfo[eState].min_x = 0;
		m_NineGridInfo[eState].max_x = 0;
	}
	return true;
}

bool NineGridStyle::SetStateMinY(int value, IStyle::STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_NineGridInfo[eState].min_y == value) return false;
	m_NineGridInfo[eState].min_y = value;
	if (m_NineGridInfo[eState].min_y == m_NineGridInfo[eState].max_y)
	{
		m_NineGridInfo[eState].min_y = 0;
		m_NineGridInfo[eState].max_y = 0;
	}
	return true;
}

bool NineGridStyle::SetStateMaxX(int value, IStyle::STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_NineGridInfo[eState].max_x == value) return false;
	m_NineGridInfo[eState].max_x = value;
	if (m_NineGridInfo[eState].min_x == m_NineGridInfo[eState].max_x)
	{
		m_NineGridInfo[eState].min_x = 0;
		m_NineGridInfo[eState].max_x = 0;
	}
	return true;
}

bool NineGridStyle::SetStateMaxY(int value, IStyle::STYLE_STATE eState)
{
	if (eState < 0 || eState >= SS_NUM) return false;
	if (m_NineGridInfo[eState].max_y == value) return false;
	m_NineGridInfo[eState].max_y = value;
	if (m_NineGridInfo[eState].min_y == m_NineGridInfo[eState].max_y)
	{
		m_NineGridInfo[eState].min_y = 0;
		m_NineGridInfo[eState].max_y = 0;
	}
	return true;
}
