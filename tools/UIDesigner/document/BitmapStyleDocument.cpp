/*!
 * \file BitmapStyleDocument.cpp
 * \date 2-14-2012 13:54:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapStyleDocument.h"
#include "../transformer/BitmapStyleTransformer.h"
#include <tinyxml-2.6.2/tinyxml.h>

BitmapStyleDocument::BitmapStyleDocument()
{
	// TODO: 
}

BitmapStyleDocument::~BitmapStyleDocument()
{
	Reset();
}

BitmapStyleDocument& BitmapStyleDocument::GetInstance()
{
	static BitmapStyleDocument s_BitmapStyleDocument;
	return s_BitmapStyleDocument;
}

bool BitmapStyleDocument::OpenFile(const wxString& strFile)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(strFile)) return false;

	Reset();

	TiXmlElement* pElmBitmapStyleList = doc.RootElement();
	if (!pElmBitmapStyleList || strcmp(pElmBitmapStyleList->Value(), "BitmapStyleList") != 0) return false;

	// parse image list
	TiXmlElement* pElmBitmapStyle = pElmBitmapStyleList->FirstChildElement("BitmapStyle");
	while (pElmBitmapStyle)
	{
		BitmapStyle* pBitmapStyle = new BitmapStyle();
		if (!pBitmapStyle->LoadFromXml(pElmBitmapStyle)) return false;
		m_BitmapStyleMap.insert(std::make_pair(pBitmapStyle->GetId(), pBitmapStyle));
		pElmBitmapStyle = pElmBitmapStyle->NextSiblingElement("BitmapStyle");
	}

	m_strFile = strFile;

	BitmapStyleTransformer::GetInstance().UpdateListView();
	return true;
}

bool BitmapStyleDocument::SaveFile(const wxString& strFile)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmBitmapStyleList = new TiXmlElement("BitmapStyleList");
	doc.LinkEndChild(pElmBitmapStyleList);

	for (TM_BITMAP_STYLE::iterator it = m_BitmapStyleMap.begin(); it != m_BitmapStyleMap.end(); ++it)
	{
		BitmapStyle* pBitmapStyle = it->second;
		pBitmapStyle->SaveToXml(pElmBitmapStyleList);
	}

	return doc.SaveFile(strFile);
}

void BitmapStyleDocument::Reset()
{
	m_strFile = wxEmptyString;
	for (TM_BITMAP_STYLE::iterator it = m_BitmapStyleMap.begin(); it != m_BitmapStyleMap.end(); ++it)
	{
		BitmapStyle* pBitmapStyle = it->second;
		delete pBitmapStyle;
	}
	m_BitmapStyleMap.clear();
}

const wxString& BitmapStyleDocument::GetFilePath() const
{
	return m_strFile;
}

const BitmapStyle* BitmapStyleDocument::FindBitmapStyle(const wxString& strId)
{
	return InternalFindBitmapStyle(strId);
}

const BitmapStyleDocument::TM_BITMAP_STYLE& BitmapStyleDocument::GetBitmapStyleMap()
{
	return m_BitmapStyleMap;
}

bool BitmapStyleDocument::RenameBitmapStyleId(const BitmapStyle* pBitmapStyle, const wxString& strNewId)
{
	if (!pBitmapStyle) return false;

	wxString strOldId = pBitmapStyle->GetId();
	if (strOldId == strNewId) return true;
	if (FindBitmapStyle(strNewId)) return false;

	TM_BITMAP_STYLE::iterator itfound = m_BitmapStyleMap.find(strOldId);
	if (itfound == m_BitmapStyleMap.end()) return false;

	BitmapStyle* pFoundBitmapStyle = itfound->second;
	m_BitmapStyleMap.erase(itfound);

	pFoundBitmapStyle->SetId(strNewId);
	m_BitmapStyleMap.insert(std::make_pair(pFoundBitmapStyle->GetId(), pFoundBitmapStyle));

	BitmapStyleTransformer::GetInstance().UpdateListView();
	BitmapStyleTransformer::GetInstance().SetSelectedBitmapStyle(pFoundBitmapStyle);
	return true;
}

bool BitmapStyleDocument::SetStatePiece(const BitmapStyle* pBitmapStyle, const PieceInfo* pPieceInfo, IStyle::STYLE_STATE eState)
{
	if (!pBitmapStyle) return false;

	BitmapStyle* pFoundBitmapStyle = InternalFindBitmapStyle(pBitmapStyle->GetId());
	if (!pFoundBitmapStyle) return false;

	return pFoundBitmapStyle->SetStatePiece(pPieceInfo, eState);
}

BitmapStyle* BitmapStyleDocument::InternalFindBitmapStyle(const wxString& strId)
{
	TM_BITMAP_STYLE::iterator itfound = m_BitmapStyleMap.find(strId);
	if (itfound == m_BitmapStyleMap.end()) return NULL;
	return itfound->second;
}
