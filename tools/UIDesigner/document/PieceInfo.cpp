/*!
 * \file PieceInfo.cpp
 * \date 2-13-2012 19:33:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PieceInfo.h"
#include "ImagePieceDocument.h"

PieceInfo::PieceInfo()
{
	m_pImageInfo = NULL;
}

PieceInfo::~PieceInfo()
{
	// TODO: 
}

bool PieceInfo::LoadFromXml(TiXmlElement* pElmPiece)
{
	if (!pElmPiece) return false;

	const char* pszId = pElmPiece->Attribute("id");
	if (!pszId) return false;
	m_strId = pszId;

	const char* pszImageId = pElmPiece->Attribute("image_id");
	if (!pszImageId) return false;

	m_pImageInfo = ImagePieceDocument::GetInstance().FindImageInfo(pszImageId);
	if (!m_pImageInfo) return false;

	if (!pElmPiece->Attribute("x", &m_Rect.x)) return false;
	if (!pElmPiece->Attribute("y", &m_Rect.y)) return false;
	if (!pElmPiece->Attribute("width", &m_Rect.width)) return false;
	if (!pElmPiece->Attribute("height", &m_Rect.height)) return false;

	return true;
}

bool PieceInfo::SaveToXml(TiXmlElement* pElmPieceList)
{
	TiXmlElement* pElmPiece = new TiXmlElement("Piece");

	pElmPiece->SetAttribute("id", m_strId);
	pElmPiece->SetAttribute("image_id", m_pImageInfo->GetId());

	pElmPiece->SetAttribute("x", m_Rect.x);
	pElmPiece->SetAttribute("y", m_Rect.y);
	pElmPiece->SetAttribute("width", m_Rect.width);
	pElmPiece->SetAttribute("height", m_Rect.height);

	pElmPieceList->LinkEndChild(pElmPiece);

	return true;
}

void PieceInfo::SetId(const wxString& strId)
{
	m_strId = strId;
}

const wxString& PieceInfo::GetId() const
{
	return m_strId;
}

void PieceInfo::SetImageInfo(ImageInfo* pImageInfo)
{
	m_pImageInfo = pImageInfo;
}

ImageInfo* PieceInfo::GetImageInfo()
{
	return m_pImageInfo;
}

void PieceInfo::SetRect(const wxRect& rect)
{
	m_Rect = rect;
}

const wxRect& PieceInfo::GetRect() const
{
	return m_Rect;
}

void PieceInfo::SetTreeItemId(wxTreeItemId itemId)
{
	m_TreeItemId = itemId;
}

wxTreeItemId PieceInfo::GetTreeItemId()
{
	return m_TreeItemId;
}
