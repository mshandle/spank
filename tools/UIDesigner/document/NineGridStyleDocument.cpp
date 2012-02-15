/*!
 * \file NineGridStyleDocument.cpp
 * \date 2-14-2012 15:40:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NineGridStyleDocument.h"
#include "../transformer/NineGridStyleTransformer.h"
#include <tinyxml-2.6.2/tinyxml.h>

NineGridStyleDocument::NineGridStyleDocument()
{
	// TODO: 
}

NineGridStyleDocument::~NineGridStyleDocument()
{
	Reset();
}

NineGridStyleDocument& NineGridStyleDocument::GetInstance()
{
	static NineGridStyleDocument s_NineGridStyleDocument;
	return s_NineGridStyleDocument;
}

bool NineGridStyleDocument::OpenFile(const wxString& strFile)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(strFile)) return false;

	Reset();

	TiXmlElement* pElmNineGridStyleList = doc.RootElement();
	if (!pElmNineGridStyleList || strcmp(pElmNineGridStyleList->Value(), "NineGridStyleList") != 0) return false;

	// parse image list
	TiXmlElement* pElmNineGridStyle = pElmNineGridStyleList->FirstChildElement("NineGridStyle");
	while (pElmNineGridStyle)
	{
		NineGridStyle* pNineGridStyle = new NineGridStyle();
		if (!pNineGridStyle->LoadFromXml(pElmNineGridStyle)) return false;
		m_NineGridStyleMap.insert(std::make_pair(pNineGridStyle->GetId(), pNineGridStyle));
		pElmNineGridStyle = pElmNineGridStyle->NextSiblingElement("NineGridStyle");
	}

	m_strFile = strFile;

	NineGridStyleTransformer::GetInstance().UpdateListView();
	return true;
}

bool NineGridStyleDocument::SaveFile(const wxString& strFile)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmNineGridStyleList = new TiXmlElement("NineGridStyleList");
	doc.LinkEndChild(pElmNineGridStyleList);

	for (TM_NINE_GRID_STYLE::iterator it = m_NineGridStyleMap.begin(); it != m_NineGridStyleMap.end(); ++it)
	{
		NineGridStyle* pNineGridStyle = it->second;
		pNineGridStyle->SaveToXml(pElmNineGridStyleList);
	}

	return doc.SaveFile(strFile);
}

void NineGridStyleDocument::Reset()
{
	m_strFile = wxEmptyString;
	for (TM_NINE_GRID_STYLE::iterator it = m_NineGridStyleMap.begin(); it != m_NineGridStyleMap.end(); ++it)
	{
		NineGridStyle* pNineGridStyle = it->second;
		delete pNineGridStyle;
	}
	m_NineGridStyleMap.clear();
}

const wxString& NineGridStyleDocument::GetFilePath() const
{
	return m_strFile;
}

NineGridStyle* NineGridStyleDocument::FindNineGridStyle(const wxString& strId)
{
	TM_NINE_GRID_STYLE::iterator itfound = m_NineGridStyleMap.find(strId);
	if (itfound == m_NineGridStyleMap.end()) return NULL;
	return itfound->second;
}

NineGridStyleDocument::TM_NINE_GRID_STYLE& NineGridStyleDocument::GetNineGridStyleMap()
{
	return m_NineGridStyleMap;
}

bool NineGridStyleDocument::RenameNineGridStyleId(const NineGridStyle* pNineGridStyle, const wxString& strNewId)
{
	if (!pNineGridStyle) return false;

	wxString strOldId = pNineGridStyle->GetId();
	if (strOldId == strNewId) return true;
	if (FindNineGridStyle(strNewId)) return false;

	TM_NINE_GRID_STYLE::iterator itfound = m_NineGridStyleMap.find(strOldId);
	if (itfound == m_NineGridStyleMap.end()) return false;

	NineGridStyle* pFoundNineGridStyle = itfound->second;
	m_NineGridStyleMap.erase(itfound);

	pFoundNineGridStyle->SetId(strNewId);
	m_NineGridStyleMap.insert(std::make_pair(pFoundNineGridStyle->GetId(), pFoundNineGridStyle));

	NineGridStyleTransformer::GetInstance().UpdateListView();
	NineGridStyleTransformer::GetInstance().SetSelectedNineGridStyle(pFoundNineGridStyle);
	return true;
}

bool NineGridStyleDocument::SetStatePiece(const NineGridStyle* pNineGridStyle, PieceInfo* pPieceInfo, IStyle::STYLE_STATE eState)
{
	if (!pNineGridStyle) return false;

	NineGridStyle* pFoundNineGridStyle = FindNineGridStyle(pNineGridStyle->GetId());
	if (!pFoundNineGridStyle) return false;

	return pFoundNineGridStyle->SetStatePiece(pPieceInfo, eState);
}

bool NineGridStyleDocument::SetStateMinX(const NineGridStyle* pNineGridStyle, int value, IStyle::STYLE_STATE eState)
{
	if (!pNineGridStyle) return false;

	NineGridStyle* pFoundNineGridStyle = FindNineGridStyle(pNineGridStyle->GetId());
	if (!pFoundNineGridStyle) return false;

	return pFoundNineGridStyle->SetStateMinX(value, eState);
}

bool NineGridStyleDocument::SetStateMinY(const NineGridStyle* pNineGridStyle, int value, IStyle::STYLE_STATE eState)
{
	if (!pNineGridStyle) return false;

	NineGridStyle* pFoundNineGridStyle = FindNineGridStyle(pNineGridStyle->GetId());
	if (!pFoundNineGridStyle) return false;

	return pFoundNineGridStyle->SetStateMinY(value, eState);
}

bool NineGridStyleDocument::SetStateMaxX(const NineGridStyle* pNineGridStyle, int value, IStyle::STYLE_STATE eState)
{
	if (!pNineGridStyle) return false;

	NineGridStyle* pFoundNineGridStyle = FindNineGridStyle(pNineGridStyle->GetId());
	if (!pFoundNineGridStyle) return false;

	return pFoundNineGridStyle->SetStateMaxX(value, eState);
}

bool NineGridStyleDocument::SetStateMaxY(const NineGridStyle* pNineGridStyle, int value, IStyle::STYLE_STATE eState)
{
	if (!pNineGridStyle) return false;

	NineGridStyle* pFoundNineGridStyle = FindNineGridStyle(pNineGridStyle->GetId());
	if (!pFoundNineGridStyle) return false;

	return pFoundNineGridStyle->SetStateMaxY(value, eState);
}
