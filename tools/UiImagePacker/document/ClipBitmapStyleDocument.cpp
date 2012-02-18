/*!
 * \file ClipBitmapStyleDocument.cpp
 * \date 2-14-2012 16:48:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ClipBitmapStyleDocument.h"
#include <tinyxml-2.6.2/tinyxml.h>
#include <wx/msgdlg.h>
#include "../ImagePackerFrame.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

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
	SetFilePath(strFile);

	TiXmlElement* pElmClipBitmapStyleList = doc.RootElement();
	if (!pElmClipBitmapStyleList || strcmp(pElmClipBitmapStyleList->Value(), "ClipBitmapStyleList") != 0) return false;

	// parse image list
	TiXmlElement* pElmClipBitmapStyle = pElmClipBitmapStyleList->FirstChildElement("ClipBitmapStyle");
	while (pElmClipBitmapStyle)
	{
		ClipBitmapStyle* pClipBitmapStyle = new ClipBitmapStyle();
		if (!pClipBitmapStyle->LoadFromXml(pElmClipBitmapStyle))
		{
			wxMessageDialog msg(&ImagePackerFrame::GetInstance(), wxString::Format("load clip bitmap style failed, id=%s", pClipBitmapStyle->GetId()));
			msg.ShowModal();
			SAFE_DELETE(pClipBitmapStyle);
			SetModifiedFlag();
		}
		else
		{
			m_ClipBitmapStyleMap.insert(std::make_pair(pClipBitmapStyle->GetId(), pClipBitmapStyle));
		}
		pElmClipBitmapStyle = pElmClipBitmapStyle->NextSiblingElement("ClipBitmapStyle");
	}

	return true;
}

bool ClipBitmapStyleDocument::SaveFile(const wxString& strFile)
{
	if (!IsModified()) return true;
	ClearModifiedFlag();

	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmClipBitmapStyleList = new TiXmlElement("ClipBitmapStyleList");
	doc.LinkEndChild(pElmClipBitmapStyleList);

	for (TM_CLIP_BITMAP_STYLE::iterator it = m_ClipBitmapStyleMap.begin(); it != m_ClipBitmapStyleMap.end(); ++it)
	{
		ClipBitmapStyle* pClipBitmapStyle = it->second;
		if (!pClipBitmapStyle->SaveToXml(pElmClipBitmapStyleList))
		{
			wxMessageDialog msg(&ImagePackerFrame::GetInstance(), wxString::Format("save clip bitmap style failed, id=%s", pClipBitmapStyle->GetId()));
			msg.ShowModal();
		}
	}

	return doc.SaveFile(strFile);
}

void ClipBitmapStyleDocument::Reset()
{
	SetFilePath(wxEmptyString);
	for (TM_CLIP_BITMAP_STYLE::iterator it = m_ClipBitmapStyleMap.begin(); it != m_ClipBitmapStyleMap.end(); ++it)
	{
		ClipBitmapStyle* pClipBitmapStyle = it->second;
		SAFE_DELETE(pClipBitmapStyle);
	}
	m_ClipBitmapStyleMap.clear();
	ClearModifiedFlag();
}

const ClipBitmapStyle* ClipBitmapStyleDocument::FindClipBitmapStyle(const wxString& strId)
{
	return InternalFindClipBitmapStyle(strId);
}

const ClipBitmapStyleDocument::TM_CLIP_BITMAP_STYLE& ClipBitmapStyleDocument::GetClipBitmapStyleMap()
{
	return m_ClipBitmapStyleMap;
}

int ClipBitmapStyleDocument::EnumClipBitmapStyles(TV_CLIP_BITMAP_STYLE& vClipBitmapStyleOut, const PieceInfo* pPieceInfo)
{
	int nFound = 0;
	for (TM_CLIP_BITMAP_STYLE::const_iterator it = m_ClipBitmapStyleMap.begin(); it != m_ClipBitmapStyleMap.end(); ++it)
	{
		const ClipBitmapStyle* pClipBitmapStyle = it->second;
		if (pClipBitmapStyle->GetStatePiece(IStyle::SS_NORMAL) == pPieceInfo
			|| pClipBitmapStyle->GetStatePiece(IStyle::SS_DOWN) == pPieceInfo
			|| pClipBitmapStyle->GetStatePiece(IStyle::SS_HOVER) == pPieceInfo
			|| pClipBitmapStyle->GetStatePiece(IStyle::SS_DISABLED) == pPieceInfo)
		{
			vClipBitmapStyleOut.push_back(pClipBitmapStyle);
			nFound++;
		}
	}

	return nFound;
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

const ClipBitmapStyle* ClipBitmapStyleDocument::AddClipBitmapStyle(const wxString& strId)
{
	if (strId.empty()) return NULL;
	SetModifiedFlag();

	wxString strNewId = GenerateNewClipBitmapStyleId(strId);
	ClipBitmapStyle* pNewClipBitmapStyle = new ClipBitmapStyle();
	pNewClipBitmapStyle->SetId(strNewId);
	m_ClipBitmapStyleMap.insert(std::make_pair(pNewClipBitmapStyle->GetId(), pNewClipBitmapStyle));

	return pNewClipBitmapStyle;
}

bool ClipBitmapStyleDocument::RemoveClipBitmapStyle(const wxString& strId)
{
	TM_CLIP_BITMAP_STYLE::iterator itfound = m_ClipBitmapStyleMap.find(strId);
	if (itfound == m_ClipBitmapStyleMap.end()) return false;
	SetModifiedFlag();

	ClipBitmapStyle* pFoundClipBitmapStyle = (itfound->second);
	m_ClipBitmapStyleMap.erase(itfound);
	SAFE_DELETE(pFoundClipBitmapStyle);

	return true;
}

ClipBitmapStyle* ClipBitmapStyleDocument::InternalFindClipBitmapStyle(const wxString& strId)
{
	TM_CLIP_BITMAP_STYLE::iterator itfound = m_ClipBitmapStyleMap.find(strId);
	if (itfound == m_ClipBitmapStyleMap.end()) return NULL;
	return itfound->second;
}

wxString ClipBitmapStyleDocument::GenerateNewClipBitmapStyleId(const wxString& strId)
{
	wxString strNewId = strId;
	int index = 0;

	while (FindClipBitmapStyle(strNewId))
	{
		strNewId = wxString::Format("%s%d", strId, index++);
	}

	return strNewId;
}