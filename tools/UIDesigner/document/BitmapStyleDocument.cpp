/*!
 * \file BitmapStyleDocument.cpp
 * \date 2-14-2012 13:54:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapStyleDocument.h"
#include <tinyxml-2.6.2/tinyxml.h>
#include <wx/msgdlg.h>
#include "../DesignerFrame.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

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
	SetFilePath(strFile);

	TiXmlElement* pElmBitmapStyleList = doc.RootElement();
	if (!pElmBitmapStyleList || strcmp(pElmBitmapStyleList->Value(), "BitmapStyleList") != 0) return false;

	// parse image list
	TiXmlElement* pElmBitmapStyle = pElmBitmapStyleList->FirstChildElement("BitmapStyle");
	while (pElmBitmapStyle)
	{
		BitmapStyle* pBitmapStyle = new BitmapStyle();
		if (!pBitmapStyle->LoadFromXml(pElmBitmapStyle))
		{
			wxMessageDialog msg(&DesignerFrame::GetInstance(), wxString::Format("load bitmap style failed, id=%s", pBitmapStyle->GetId()));
			msg.ShowModal();
			SAFE_DELETE(pBitmapStyle);
		}
		else
		{
			m_BitmapStyleMap.insert(std::make_pair(pBitmapStyle->GetId(), pBitmapStyle));
		}

		pElmBitmapStyle = pElmBitmapStyle->NextSiblingElement("BitmapStyle");
	}

	return true;
}

bool BitmapStyleDocument::SaveFile(const wxString& strFile)
{
	if (!isModified()) return true;
	ClearModifiedFlag();

	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmBitmapStyleList = new TiXmlElement("BitmapStyleList");
	doc.LinkEndChild(pElmBitmapStyleList);

	for (TM_BITMAP_STYLE::iterator it = m_BitmapStyleMap.begin(); it != m_BitmapStyleMap.end(); ++it)
	{
		BitmapStyle* pBitmapStyle = it->second;
		if (!pBitmapStyle->SaveToXml(pElmBitmapStyleList))
		{
			wxMessageDialog msg(&DesignerFrame::GetInstance(), wxString::Format("save bitmap style failed, id=%s", pBitmapStyle->GetId()));
			msg.ShowModal();
		}
	}

	return doc.SaveFile(strFile);
}

void BitmapStyleDocument::Reset()
{
	for (TM_BITMAP_STYLE::iterator it = m_BitmapStyleMap.begin(); it != m_BitmapStyleMap.end(); ++it)
	{
		BitmapStyle* pBitmapStyle = it->second;
		SAFE_DELETE(pBitmapStyle);
	}
	m_BitmapStyleMap.clear();
	ClearModifiedFlag();
}

const BitmapStyle* BitmapStyleDocument::FindBitmapStyle(const wxString& strId)
{
	return InternalFindBitmapStyle(strId);
}

const BitmapStyleDocument::TM_BITMAP_STYLE& BitmapStyleDocument::GetBitmapStyleMap()
{
	return m_BitmapStyleMap;
}

int BitmapStyleDocument::EnumBitmapStyles(TV_BITMAP_STYLE& vBitmapStyleOut, const PieceInfo* pPieceInfo)
{
	int nFound = 0;
	for (TM_BITMAP_STYLE::const_iterator it = m_BitmapStyleMap.begin(); it != m_BitmapStyleMap.end(); ++it)
	{
		const BitmapStyle* pBitmapStyle = it->second;
		if (pBitmapStyle->GetStatePiece(IStyle::SS_NORMAL) == pPieceInfo
			|| pBitmapStyle->GetStatePiece(IStyle::SS_DOWN) == pPieceInfo
			|| pBitmapStyle->GetStatePiece(IStyle::SS_HOVER) == pPieceInfo
			|| pBitmapStyle->GetStatePiece(IStyle::SS_DISABLED) == pPieceInfo)
		{
			vBitmapStyleOut.push_back(pBitmapStyle);
			nFound++;
		}
	}

	return nFound;
}

bool BitmapStyleDocument::RenameBitmapStyleId(const BitmapStyle* pBitmapStyle, const wxString& strNewId)
{
	if (!pBitmapStyle) return false;

	wxString strOldId = pBitmapStyle->GetId();
	if (strOldId == strNewId) return true;
	if (FindBitmapStyle(strNewId)) return false;

	TM_BITMAP_STYLE::iterator itfound = m_BitmapStyleMap.find(strOldId);
	if (itfound == m_BitmapStyleMap.end()) return false;
	SetModifiedFlag();

	BitmapStyle* pFoundBitmapStyle = itfound->second;
	m_BitmapStyleMap.erase(itfound);

	pFoundBitmapStyle->SetId(strNewId);
	m_BitmapStyleMap.insert(std::make_pair(pFoundBitmapStyle->GetId(), pFoundBitmapStyle));

	return true;
}

bool BitmapStyleDocument::SetStatePiece(const BitmapStyle* pBitmapStyle, const PieceInfo* pPieceInfo, IStyle::STYLE_STATE eState)
{
	if (!pBitmapStyle) return false;

	BitmapStyle* pFoundBitmapStyle = InternalFindBitmapStyle(pBitmapStyle->GetId());
	if (!pFoundBitmapStyle) return false;
	SetModifiedFlag();

	return pFoundBitmapStyle->SetStatePiece(pPieceInfo, eState);
}

const BitmapStyle* BitmapStyleDocument::AddBitmapStyle(const wxString& strId)
{
	if (strId.empty()) return NULL;
	SetModifiedFlag();

	wxString strNewId = GenerateNewBitmapStyleId(strId);
	BitmapStyle* pNewBitmapStyle = new BitmapStyle();
	pNewBitmapStyle->SetId(strNewId);
	m_BitmapStyleMap.insert(std::make_pair(pNewBitmapStyle->GetId(), pNewBitmapStyle));

	return pNewBitmapStyle;
}

bool BitmapStyleDocument::RemoveBitmapStyle(const wxString& strId)
{
	TM_BITMAP_STYLE::iterator itfound = m_BitmapStyleMap.find(strId);
	if (itfound == m_BitmapStyleMap.end()) return false;
	SetModifiedFlag();

	BitmapStyle* pFoundBitmapStyle = itfound->second;
	m_BitmapStyleMap.erase(itfound);

	SAFE_DELETE(pFoundBitmapStyle);
	return true;
}

BitmapStyle* BitmapStyleDocument::InternalFindBitmapStyle(const wxString& strId)
{
	TM_BITMAP_STYLE::iterator itfound = m_BitmapStyleMap.find(strId);
	if (itfound == m_BitmapStyleMap.end()) return NULL;
	return itfound->second;
}

wxString BitmapStyleDocument::GenerateNewBitmapStyleId(const wxString& strId)
{
	wxString strNewId = strId;
	int index = 0;

	while (FindBitmapStyle(strNewId))
	{
		strNewId = wxString::Format("%s%d", strId, index++);
	}

	return strNewId;
}
