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
	// TODO: 
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
	m_ImageMap.clear();
	TiXmlElement* pElmImage = pElmImageList->FirstChildElement("Image");
	while (pElmImage)
	{
		IMAGE_INFO imageInfo;

		if (!pElmImage->Attribute("id", &imageInfo.nId)) return false;
		imageInfo.strFile = pElmImage->Attribute("file");

		m_ImageMap.insert(std::make_pair(imageInfo.nId, imageInfo));

		pElmImage = pElmImage->NextSiblingElement("Image");
	}

	TiXmlElement* pElmPieceList = pElmImagePiece->FirstChildElement("PieceList");
	// parse piece list
	m_PieceInfoMap.clear();
	TiXmlElement* pElmPiece = pElmPieceList->FirstChildElement("Piece");
	while (pElmPiece)
	{
		PIECE_INFO pieceInfo;
		pieceInfo.strId = pElmPiece->Attribute("id");

		if (!pElmPiece->Attribute("image", &pieceInfo.nImageId)) return false;

		if (!pElmPiece->Attribute("x", &pieceInfo.pieceRect.x)) return false;
		if (!pElmPiece->Attribute("y", &pieceInfo.pieceRect.y)) return false;
		if (!pElmPiece->Attribute("width", &pieceInfo.pieceRect.width)) return false;
		if (!pElmPiece->Attribute("height", &pieceInfo.pieceRect.height)) return false;

		m_PieceInfoMap.insert(std::make_pair(pieceInfo.strId, pieceInfo));

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

	for (TM_IMAGE_INFO::const_iterator it = m_ImageMap.begin(); it != m_ImageMap.end(); ++it)
	{
		const IMAGE_INFO& imageInfo = it->second;
		TiXmlElement* pElmImage = new TiXmlElement("Image");
		pElmImage->SetAttribute("id", imageInfo.nId);
		pElmImage->SetAttribute("file", imageInfo.strFile);
		pElmImageList->LinkEndChild(pElmImage);
	}

	TiXmlElement* pElmPieceList = new TiXmlElement("PieceList");
	pElmImagePiece->LinkEndChild(pElmPieceList);

	for (TM_PIECE_INFO::const_iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		const PIECE_INFO& pieceInfo = it->second;
		TiXmlElement* pElmPiece = new TiXmlElement("Piece");
		pElmPiece->SetAttribute("id", pieceInfo.strId);
		pElmPiece->SetAttribute("image", pieceInfo.nImageId);
		pElmPiece->SetAttribute("x", pieceInfo.pieceRect.x);
		pElmPiece->SetAttribute("y", pieceInfo.pieceRect.y);
		pElmPiece->SetAttribute("width", pieceInfo.pieceRect.width);
		pElmPiece->SetAttribute("height", pieceInfo.pieceRect.height);

		pElmPieceList->LinkEndChild(pElmPiece);
	}

	return doc.SaveFile(strFile);
}

const wxString& UIImagePieceDocument::GetFileName() const
{
	return m_strFile;
}

 UIImagePieceDocument::TM_IMAGE_INFO& UIImagePieceDocument::GetImageMap()
{
	return m_ImageMap;
}

const wxString& UIImagePieceDocument::FindImage(int nID) const
{
	static const wxString s_strEmptyString = wxEmptyString;

	TM_IMAGE_INFO::const_iterator itfound = m_ImageMap.find(nID);
	if (itfound == m_ImageMap.end()) return s_strEmptyString;
	return (itfound->second).strFile;
}

 UIImagePieceDocument::TM_PIECE_INFO& UIImagePieceDocument::GetPieceInfoMap() 
{
	return m_PieceInfoMap;
}

 UIImagePieceDocument::PIECE_INFO* UIImagePieceDocument::FindPieceInfo(const wxString& strID) 
{
	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(strID);
	if (itfound == m_PieceInfoMap.end()) return NULL;
	return &itfound->second;
}

void UIImagePieceDocument::UpdateImagePiece(const PIECE_INFO& pieceInfo)
{
	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(pieceInfo.strId);
	if (itfound == m_PieceInfoMap.end()) return;

	PIECE_INFO* pPieceInfo = &itfound->second;
	pPieceInfo->nImageId = pieceInfo.nImageId;
	pPieceInfo->pieceRect = pieceInfo.pieceRect;
}

void UIImagePieceDocument::AddPieceInfo(const PIECE_INFO& PieceInfo)
{
	if(FindPieceInfo(PieceInfo.strId) != NULL) return;
	m_PieceInfoMap.insert(std::make_pair(PieceInfo.strId, PieceInfo));
}

void UIImagePieceDocument::AddImageInfo(const IMAGE_INFO& ImageInfo)
{
	if(FindImage(ImageInfo.nId) != wxEmptyString) return;
	m_ImageMap.insert(std::make_pair(ImageInfo.nId, ImageInfo));
}

bool UIImagePieceDocument::NewFile(const wxString& strFile)
{
	m_ImageMap.clear();
	m_PieceInfoMap.clear();
	m_strFile = strFile;
	return true;
}

void UIImagePieceDocument::Clear()
{
	m_strFile = wxEmptyString;
	m_ImageMap.clear();
	m_PieceInfoMap.clear();
}

int UIImagePieceDocument::GetImageMapKeyValue(const wxString& strValue)
{
	for (TM_IMAGE_INFO::iterator it = m_ImageMap.begin(); it != m_ImageMap.end(); ++it)
	{
		if(it->second.strFile == strValue)
			return it->second.nId;
	}
	return 0;
}