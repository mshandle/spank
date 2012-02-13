/*!
 * \file UIImagePieceDocument.cpp
 * \date 11-09-2011 08:22:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIImagePieceDocument.h"
#include <tinyxml-2.6.2/tinyxml.h>

UIImagePieceDocument::UIImagePieceDocument()
{
	// TODO: 
}

UIImagePieceDocument::~UIImagePieceDocument()
{
	Clear();
}

bool UIImagePieceDocument::OpenFile(const wxString& strFile)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(strFile)) return false;

	TiXmlElement* pElmImagePiece = doc.RootElement();
	if (!pElmImagePiece || strcmp(pElmImagePiece->Value(), "ImagePiece") != 0) return false;

	TiXmlElement* pElmImageList = pElmImagePiece->FirstChildElement("ImageList");
	if (!pElmImageList) return false;

	// parse image list
	m_ImageInfoMap.clear();
	TiXmlElement* pElmImage = pElmImageList->FirstChildElement("Image");
	while (pElmImage)
	{
		ImageInfo* pImageInfo = new ImageInfo();
		if (!pImageInfo->LoadFromXml(pElmImage)) return false;
		m_ImageInfoMap.insert(std::make_pair(pImageInfo->GetId(), pImageInfo));
		pElmImage = pElmImage->NextSiblingElement("Image");
	}

	TiXmlElement* pElmPieceList = pElmImagePiece->FirstChildElement("PieceList");
	// parse piece list
	m_PieceInfoMap.clear();
	TiXmlElement* pElmPiece = pElmPieceList->FirstChildElement("Piece");
	while (pElmPiece)
	{
		PieceInfo* pPieceInfo = new PieceInfo();
		if (!pPieceInfo->LoadFromXml(pElmPiece)) return false;
		m_PieceInfoMap.insert(std::make_pair(pPieceInfo->GetId(), pPieceInfo));
		pElmPiece = pElmPiece->NextSiblingElement("Piece");
	}

	m_strFile = strFile;
	return true;
}

bool UIImagePieceDocument::SaveFile(const wxString& strFile)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmImagePiece = new TiXmlElement("ImagePiece");
	doc.LinkEndChild(pElmImagePiece);

	TiXmlElement* pElmImageList = new TiXmlElement("ImageList");
	pElmImagePiece->LinkEndChild(pElmImageList);

	for (TM_IMAGE_INFO::const_iterator it = m_ImageInfoMap.begin(); it != m_ImageInfoMap.end(); ++it)
	{
		const ImageInfo* pImageInfo = it->second;
		TiXmlElement* pElmImage = new TiXmlElement("Image");
		pElmImage->SetAttribute("id", pImageInfo->GetId());
		pElmImage->SetAttribute("file", pImageInfo->GetPath());
		pElmImageList->LinkEndChild(pElmImage);
	}

	TiXmlElement* pElmPieceList = new TiXmlElement("PieceList");
	pElmImagePiece->LinkEndChild(pElmPieceList);

	for (TM_PIECE_INFO::const_iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		const PieceInfo* pPieceInfo = it->second;
		TiXmlElement* pElmPiece = new TiXmlElement("Piece");
		pElmPiece->SetAttribute("id", pPieceInfo->GetId());
		pElmPiece->SetAttribute("image", pPieceInfo->GetImageId());

		pElmPiece->SetAttribute("x", pPieceInfo->GetRect().x);
		pElmPiece->SetAttribute("y", pPieceInfo->GetRect().y);
		pElmPiece->SetAttribute("width", pPieceInfo->GetRect().width);
		pElmPiece->SetAttribute("height", pPieceInfo->GetRect().height);

		pElmPieceList->LinkEndChild(pElmPiece);
	}

	return doc.SaveFile(strFile);
}

const wxString& UIImagePieceDocument::GetFileName() const
{
	return m_strFile;
}

ImageInfo* UIImagePieceDocument::FindImageInfo(const wxString& strId)
{
	TM_IMAGE_INFO::iterator itfound = m_ImageInfoMap.find(strId);
	if (itfound == m_ImageInfoMap.end()) return NULL;
	return itfound->second;
}

PieceInfo* UIImagePieceDocument::FindPieceInfo(const wxString& strId)
{
	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(strId);
	if (itfound == m_PieceInfoMap.end()) return NULL;
	return itfound->second;
}

bool UIImagePieceDocument::NewFile(const wxString& strFile)
{
	Clear();
	m_strFile = strFile;
	return true;
}

void UIImagePieceDocument::Clear()
{
	m_strFile = wxEmptyString;
	for (TM_IMAGE_INFO::iterator it = m_ImageInfoMap.begin(); it != m_ImageInfoMap.end(); ++it)
	{
		ImageInfo* pImageInfo = it->second;
		delete pImageInfo;
	}
	m_ImageInfoMap.clear();

	for (TM_PIECE_INFO::iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		delete pPieceInfo;
	}
	m_PieceInfoMap.clear();
}

const UIImagePieceDocument::TM_IMAGE_INFO& UIImagePieceDocument::GetImageInfoMap() const
{
	return m_ImageInfoMap;
}

const UIImagePieceDocument::TM_PIECE_INFO& UIImagePieceDocument::GetPieceInfoMap() const
{
	return m_PieceInfoMap;
}
