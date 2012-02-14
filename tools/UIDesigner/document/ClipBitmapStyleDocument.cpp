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
}

const wxString& ClipBitmapStyleDocument::GetFilePath() const
{
	return m_strFile;
}

ClipBitmapStyle* ClipBitmapStyleDocument::FindClipBitmapStyle(const wxString& strId)
{
	TM_CLIP_BITMAP_STYLE::iterator itfound = m_ClipBitmapStyleMap.find(strId);
	if (itfound == m_ClipBitmapStyleMap.end()) return NULL;
	return itfound->second;
}

ClipBitmapStyleDocument::TM_CLIP_BITMAP_STYLE& ClipBitmapStyleDocument::GetClipBitmapStyleMap()
{
	return m_ClipBitmapStyleMap;
}
