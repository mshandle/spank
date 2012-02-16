/*!
 * \file ClipBitmapStyleDocument.cpp
 * \date 2-14-2012 16:48:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ClipBitmapStyleDocument.h"
#include "../transformer/ClipBitmapStyleTransformer.h"
#include <tinyxml-2.6.2/tinyxml.h>

ClipBitmapStyleDocument::ClipBitmapStyleDocument()
{
	// TODO: 
}

ClipBitmapStyleDocument::~ClipBitmapStyleDocument()
{
	Reset();
}

ClipBitmapStyleDocument& ClipBitmapStyleDocument::GetInstance()
{
	static ClipBitmapStyleDocument s_ClipBitmapStyleDocument;
	return s_ClipBitmapStyleDocument;
}

bool ClipBitmapStyleDocument::OpenFile(const wxString& strFile)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(strFile)) return false;

	Reset();

	TiXmlElement* pElmClipBitmapStyleList = doc.RootElement();
	if (!pElmClipBitmapStyleList || strcmp(pElmClipBitmapStyleList->Value(), "ClipBitmapStyleList") != 0) return false;

	// parse image list
	TiXmlElement* pElmClipBitmapStyle = pElmClipBitmapStyleList->FirstChildElement("ClipBitmapStyle");
	while (pElmClipBitmapStyle)
	{
		ClipBitmapStyle* pClipBitmapStyle = new ClipBitmapStyle();
		if (!pClipBitmapStyle->LoadFromXml(pElmClipBitmapStyle)) return false;
		m_ClipBitmapStyleMap.insert(std::make_pair(pClipBitmapStyle->GetId(), pClipBitmapStyle));
		pElmClipBitmapStyle = pElmClipBitmapStyle->NextSiblingElement("ClipBitmapStyle");
	}

	m_strFile = strFile;

	ClipBitmapStyleTransformer::GetInstance().UpdateListView();
	return true;
}

bool ClipBitmapStyleDocument::SaveFile(const wxString& strFile)
{
	if (!isModified()) return true;
	ClearModifiedFlag();

	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmClipBitmapStyleList = new TiXmlElement("ClipBitmapStyleList");
	doc.LinkEndChild(pElmClipBitmapStyleList);

	for (TM_CLIP_BITMAP_STYLE::iterator it = m_ClipBitmapStyleMap.begin(); it != m_ClipBitmapStyleMap.end(); ++it)
	{
		ClipBitmapStyle* pClipBitmapStyle = it->second;
		pClipBitmapStyle->SaveToXml(pElmClipBitmapStyleList);
	}

	return doc.SaveFile(strFile);
}

void ClipBitmapStyleDocument::Reset()
{
	m_strFile = wxEmptyString;
	for (TM_CLIP_BITMAP_STYLE::iterator it = m_ClipBitmapStyleMap.begin(); it != m_ClipBitmapStyleMap.end(); ++it)
	{
		ClipBitmapStyle* pClipBitmapStyle = it->second;
		delete pClipBitmapStyle;
	}
	m_ClipBitmapStyleMap.clear();
	ClearModifiedFlag();
}

const wxString& ClipBitmapStyleDocument::GetFilePath() const
{
	return m_strFile;
}

const ClipBitmapStyle* ClipBitmapStyleDocument::FindClipBitmapStyle(const wxString& strId)
{
	return InternalFindClipBitmapStyle(strId);
}

const ClipBitmapStyleDocument::TM_CLIP_BITMAP_STYLE& ClipBitmapStyleDocument::GetClipBitmapStyleMap()
{
	return m_ClipBitmapStyleMap;
}

bool ClipBitmapStyleDocument::RenameClipBitmapStyleId(const ClipBitmapStyle* pClipBitmapStyle, const wxString& strNewId)
{
	if (!pClipBitmapStyle) return false;

	wxString strOldId = pClipBitmapStyle->GetId();
	if (strOldId == strNewId) return true;
	if (FindClipBitmapStyle(strNewId)) return false;

	TM_CLIP_BITMAP_STYLE::iterator itfound = m_ClipBitmapStyleMap.find(strOldId);
	if (itfound == m_ClipBitmapStyleMap.end()) return false;
	SetModifiedFlag();

	ClipBitmapStyle* pFoundClipBitmapStyle = itfound->second;
	m_ClipBitmapStyleMap.erase(itfound);

	pFoundClipBitmapStyle->SetId(strNewId);
	m_ClipBitmapStyleMap.insert(std::make_pair(pFoundClipBitmapStyle->GetId(), pFoundClipBitmapStyle));

	ClipBitmapStyleTransformer::GetInstance().UpdateListView();
	ClipBitmapStyleTransformer::GetInstance().SetSelectedClipBitmapStyle(pFoundClipBitmapStyle);
	return true;
}

bool ClipBitmapStyleDocument::SetStatePiece(const ClipBitmapStyle* pClipBitmapStyle, const PieceInfo* pPieceInfo, IStyle::STYLE_STATE eState)
{
	if (!pClipBitmapStyle) return false;

	ClipBitmapStyle* pFoundClipBitmapStyle = InternalFindClipBitmapStyle(pClipBitmapStyle->GetId());
	if (!pFoundClipBitmapStyle) return false;
	SetModifiedFlag();

	return pFoundClipBitmapStyle->SetStatePiece(pPieceInfo, eState);
}

ClipBitmapStyle* ClipBitmapStyleDocument::InternalFindClipBitmapStyle(const wxString& strId)
{
	TM_CLIP_BITMAP_STYLE::iterator itfound = m_ClipBitmapStyleMap.find(strId);
	if (itfound == m_ClipBitmapStyleMap.end()) return NULL;
	return itfound->second;
}