/*!
 * \file PieceInfo.cpp
 * \date 2-13-2012 19:33:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PieceInfo.h"

PieceInfo::PieceInfo()
{
	// TODO: 
}

PieceInfo::~PieceInfo()
{
	// TODO: 
}

bool PieceInfo::LoadFromXml(TiXmlElement* pElmPiece)
{
	if (!pElmPiece) return false;

	m_strId = pElmPiece->Attribute("id");
	m_strImageId = pElmPiece->Attribute("image_id");

	if (!pElmPiece->Attribute("x", &m_Rect.x)) return false;
	if (!pElmPiece->Attribute("y", &m_Rect.y)) return false;
	if (!pElmPiece->Attribute("width", &m_Rect.width)) return false;
	if (!pElmPiece->Attribute("height", &m_Rect.height)) return false;

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

void PieceInfo::SetImageId(const wxString& strImageId)
{
	m_strImageId = strImageId;
}

const wxString& PieceInfo::GetImageId() const
{
	return m_strImageId;
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