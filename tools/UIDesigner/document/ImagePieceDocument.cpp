/*!
 * \file ImagePieceDocument.cpp
 * \date 2-14-2012 1:23:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImagePieceDocument.h"
#include "../transformer/ImageListTransformer.h"
#include "../transformer/PieceListTransformer.h"
#include <tinyxml-2.6.2/tinyxml.h>

ImagePieceDocument::ImagePieceDocument()
{
	// TODO: 
}

ImagePieceDocument::~ImagePieceDocument()
{
	Reset();
}

bool ImagePieceDocument::OpenFile(const wxString& strFile)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(strFile)) return false;

	Reset();

	TiXmlElement* pElmImagePiece = doc.RootElement();
	if (!pElmImagePiece || strcmp(pElmImagePiece->Value(), "ImagePiece") != 0) return false;

	TiXmlElement* pElmImageList = pElmImagePiece->FirstChildElement("ImageList");
	if (!pElmImageList) return false;

	// parse image list
	TiXmlElement* pElmImage = pElmImageList->FirstChildElement("Image");
	while (pElmImage)
	{
		ImageInfo* pImageInfo = new ImageInfo();
		if (!pImageInfo->LoadFromXml(pElmImage)) return false;
		m_ImageInfoMap.insert(std::make_pair(pImageInfo->GetId(), pImageInfo));
		pElmImage = pElmImage->NextSiblingElement("Image");
	}
	GenerateImageArrayString();

	TiXmlElement* pElmPieceList = pElmImagePiece->FirstChildElement("PieceList");
	// parse piece list
	TiXmlElement* pElmPiece = pElmPieceList->FirstChildElement("Piece");
	while (pElmPiece)
	{
		PieceInfo* pPieceInfo = new PieceInfo();
		if (!pPieceInfo->LoadFromXml(pElmPiece)) return false;
		m_PieceInfoMap.insert(std::make_pair(pPieceInfo->GetId(), pPieceInfo));
		pElmPiece = pElmPiece->NextSiblingElement("Piece");
	}
	GeneratePieceArrayString();

	m_strFile = strFile;

	ImageListTransformer::GetInstance().UpdateListView();
	PieceListTransformer::GetInstance().UpdateListView();
	return true;
}

bool ImagePieceDocument::SaveFile(const wxString& strFile)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmImagePiece = new TiXmlElement("ImagePiece");
	doc.LinkEndChild(pElmImagePiece);

	TiXmlElement* pElmImageList = new TiXmlElement("ImageList");
	pElmImagePiece->LinkEndChild(pElmImageList);
	for (TM_IMAGE_INFO::iterator it = m_ImageInfoMap.begin(); it != m_ImageInfoMap.end(); ++it)
	{
		ImageInfo* pImageInfo = it->second;
		pImageInfo->SaveToXml(pElmImageList);
	}

	TiXmlElement* pElmPieceList = new TiXmlElement("PieceList");
	pElmImagePiece->LinkEndChild(pElmPieceList);
	for (TM_PIECE_INFO::iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		pPieceInfo->SaveToXml(pElmPieceList);
	}

	return doc.SaveFile(strFile);
}

void ImagePieceDocument::Reset()
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

	m_ImageIds.Clear();
	m_ImageIdsIndex.Clear();

	m_PieceIds.Clear();
	m_PieceIdsIndex.Clear();
}

const wxString& ImagePieceDocument::GetFilePath() const
{
	return m_strFile;
}

ImagePieceDocument& ImagePieceDocument::GetInstance()
{
	static ImagePieceDocument s_UIImagePieceDocument;
	return s_UIImagePieceDocument;
}

ImageInfo* ImagePieceDocument::FindImageInfo(const wxString& strId)
{
	TM_IMAGE_INFO::iterator itfound = m_ImageInfoMap.find(strId);
	if (itfound == m_ImageInfoMap.end()) return NULL;
	return itfound->second;
}

PieceInfo* ImagePieceDocument::FindPieceInfo(const wxString& strId)
{
	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(strId);
	if (itfound == m_PieceInfoMap.end()) return NULL;
	return itfound->second;
}

PieceInfo* ImagePieceDocument::FindPieceInfoUnderPoint(const wxPoint& pos, const ImageInfo* pImageInfo)
{
	if (!pImageInfo) return NULL;

	for (TM_PIECE_INFO::iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		if (pPieceInfo->GetImageInfo() != pImageInfo) continue;

		if (pPieceInfo->GetRect().Contains(pos)) return pPieceInfo;
	}

	return NULL;
}

ImagePieceDocument::TM_IMAGE_INFO& ImagePieceDocument::GetImageInfoMap()
{
	return m_ImageInfoMap;
}

ImagePieceDocument::TM_PIECE_INFO& ImagePieceDocument::GetPieceInfoMap()
{
	return m_PieceInfoMap;
}

const wxArrayString& ImagePieceDocument::GetImageIds()
{
	return m_ImageIds;
}

const wxArrayInt& ImagePieceDocument::GetImageIdsIndex()
{
	return m_ImageIdsIndex;
}

int ImagePieceDocument::FindImageIndex(const wxString& strId)
{
	for (size_t i = 0; i < m_ImageIds.GetCount(); ++i)
	{
		if (m_ImageIds[i] == strId) return i;
	}

	return -1;
}

const wxString& ImagePieceDocument::GetImageId(int index)
{
	return m_ImageIds[index];
}

const wxArrayString& ImagePieceDocument::GetPieceIds()
{
	return m_PieceIds;
}

const wxArrayInt& ImagePieceDocument::GetPieceIdsIndex()
{
	return m_PieceIdsIndex;
}

int ImagePieceDocument::FindPieceIndex(const wxString& strId)
{
	for (size_t i = 0; i < m_PieceIdsIndex.GetCount(); ++i)
	{
		if (m_PieceIds[i] == strId) return i;
	}

	return -1;
}

const wxString& ImagePieceDocument::GetPieceId(int index)
{
	return m_PieceIds[index];
}

void ImagePieceDocument::GenerateImageArrayString()
{
	m_ImageIds.Clear();
	m_ImageIdsIndex.Clear();

	int nIndex = 0;
	for (TM_IMAGE_INFO::iterator it = m_ImageInfoMap.begin(); it != m_ImageInfoMap.end(); ++it)
	{
		m_ImageIds.Add(it->first);
		m_ImageIdsIndex.Add(nIndex++);
	}
}

void ImagePieceDocument::GeneratePieceArrayString()
{
	m_PieceIds.Clear();
	m_PieceIdsIndex.Clear();

	int nIndex = 0;
	for (TM_PIECE_INFO::iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		m_PieceIds.Add(it->first);
		m_PieceIdsIndex.Add(nIndex++);
	}
}
