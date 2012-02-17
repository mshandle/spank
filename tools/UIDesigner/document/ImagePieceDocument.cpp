/*!
 * \file ImagePieceDocument.cpp
 * \date 2-14-2012 1:23:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImagePieceDocument.h"
#include <tinyxml-2.6.2/tinyxml.h>

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

ImagePieceDocument::ImagePieceDocument()
{
	m_bNeedUpdateImageIds = false;
	m_bNeedUpdatePieceIds = false;
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
	SetFilePath(strFile);

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
	m_bNeedUpdateImageIds = true;

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
	m_bNeedUpdatePieceIds = true;

	return true;
}

bool ImagePieceDocument::SaveFile(const wxString& strFile)
{
	if (!isModified()) return true;
	ClearModifiedFlag();

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
		pImageInfo->SaveImage();
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
	SetFilePath(wxEmptyString);
	for (TM_IMAGE_INFO::iterator it = m_ImageInfoMap.begin(); it != m_ImageInfoMap.end(); ++it)
	{
		ImageInfo* pImageInfo = it->second;
		SAFE_DELETE(pImageInfo);
	}
	m_ImageInfoMap.clear();

	for (TM_PIECE_INFO::iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		SAFE_DELETE(pPieceInfo);
	}
	m_PieceInfoMap.clear();

	m_ImageIds.Clear();
	m_ImageIdsIndex.Clear();

	m_PieceIds.Clear();
	m_PieceIdsIndex.Clear();

	m_bNeedUpdateImageIds = false;
	m_bNeedUpdatePieceIds = false;

	ClearModifiedFlag();
}

ImagePieceDocument& ImagePieceDocument::GetInstance()
{
	static ImagePieceDocument s_UIImagePieceDocument;
	return s_UIImagePieceDocument;
}

const ImageInfo* ImagePieceDocument::FindImageInfo(const wxString& strId)
{
	TM_IMAGE_INFO::iterator itfound = m_ImageInfoMap.find(strId);
	if (itfound == m_ImageInfoMap.end()) return NULL;
	return itfound->second;
}

const PieceInfo* ImagePieceDocument::FindPieceInfo(const wxString& strId)
{
	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(strId);
	if (itfound == m_PieceInfoMap.end()) return NULL;
	return itfound->second;
}

const PieceInfo* ImagePieceDocument::FindPieceInfoUnderPoint(const wxPoint& pos, const ImageInfo* pImageInfo)
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

int ImagePieceDocument::EnumImagePieces(TV_PIECE_INFO& PieceOut, const ImageInfo* pImageInfo)
{
	int nFound = 0;
	for (TM_PIECE_INFO::iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		if (pPieceInfo->GetImageInfo() == pImageInfo)
		{
			PieceOut.push_back(pPieceInfo);
			nFound++;
		}
	}

	return nFound;
}

const ImagePieceDocument::TM_IMAGE_INFO& ImagePieceDocument::GetImageInfoMap()
{
	return m_ImageInfoMap;
}

const ImagePieceDocument::TM_PIECE_INFO& ImagePieceDocument::GetPieceInfoMap()
{
	return m_PieceInfoMap;
}

const wxArrayString& ImagePieceDocument::GetImageIds()
{
	UpdateImageArrayString();
	return m_ImageIds;
}

const wxArrayInt& ImagePieceDocument::GetImageIdsIndex()
{
	UpdateImageArrayString();
	return m_ImageIdsIndex;
}

int ImagePieceDocument::FindImageIndex(const wxString& strId)
{
	UpdateImageArrayString();
	for (size_t i = 0; i < m_ImageIds.GetCount(); ++i)
	{
		if (m_ImageIds[i] == strId) return i;
	}

	return 0;
}

const wxString& ImagePieceDocument::GetImageId(int index)
{
	UpdateImageArrayString();
	return m_ImageIds[index];
}

const wxArrayString& ImagePieceDocument::GetPieceIds()
{
	UpdatePieceArrayString();
	return m_PieceIds;
}

const wxArrayInt& ImagePieceDocument::GetPieceIdsIndex()
{
	UpdatePieceArrayString();
	return m_PieceIdsIndex;
}

int ImagePieceDocument::FindPieceIndex(const PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return 0;
	return FindPieceIndex(pPieceInfo->GetId());
}

int ImagePieceDocument::FindPieceIndex(const wxString& strId)
{
	UpdatePieceArrayString();
	for (size_t i = 0; i < m_PieceIds.GetCount(); ++i)
	{
		if (m_PieceIds[i] == strId) return i;
	}

	return 0;
}

const wxString& ImagePieceDocument::GetPieceId(int index)
{
	UpdatePieceArrayString();
	return m_PieceIds[index];
}

bool ImagePieceDocument::RenameImageInfoId(const ImageInfo* pImageInfo, const wxString& strNewId)
{
	if (!pImageInfo) return false;

	wxString strOldId = pImageInfo->GetId();
	if (strOldId == strNewId) return true;
	if (FindImageInfo(strNewId)) return false;

	TM_IMAGE_INFO::iterator itfound = m_ImageInfoMap.find(strOldId);
	if (itfound == m_ImageInfoMap.end()) return false;
	SetModifiedFlag();

	ImageInfo* pFoundImageInfo = itfound->second;
	m_ImageInfoMap.erase(itfound);

	pFoundImageInfo->SetId(strNewId);
	m_ImageInfoMap.insert(std::make_pair(pFoundImageInfo->GetId(), pFoundImageInfo));

	m_bNeedUpdateImageIds = true;
	return true;
}

bool ImagePieceDocument::RenamePieceInfoId(const PieceInfo* pPieceInfo, const wxString& strNewId)
{
	if (!pPieceInfo) return false;

	wxString strOldId = pPieceInfo->GetId();
	if (strOldId == strNewId) return true;
	if (FindPieceInfo(strNewId)) return false;

	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(strOldId);
	if (itfound == m_PieceInfoMap.end()) return false;
	SetModifiedFlag();

	PieceInfo* pFoundPieceInfo = itfound->second;
	m_PieceInfoMap.erase(itfound);

	pFoundPieceInfo->SetId(strNewId);
	m_PieceInfoMap.insert(std::make_pair(pFoundPieceInfo->GetId(), pFoundPieceInfo));

	m_bNeedUpdatePieceIds = true;
	return true;
}

bool ImagePieceDocument::SetImageBitmap(const ImageInfo* pImageInfo, wxBitmap* pNewBitmap)
{
	if (!pImageInfo) return false;

	TM_IMAGE_INFO::iterator itfound = m_ImageInfoMap.find(pImageInfo->GetId());
	if (itfound == m_ImageInfoMap.end()) return false;
	SetModifiedFlag();

	ImageInfo* pFoundImageInfo = itfound->second;

	pFoundImageInfo->SetBitmap(pNewBitmap);
	return true;
}

bool ImagePieceDocument::SetPieceRect(const PieceInfo* pPieceInfo, const wxRect& rect)
{
	if (!pPieceInfo) return false;

	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(pPieceInfo->GetId());
	if (itfound == m_PieceInfoMap.end()) return false;
	SetModifiedFlag();

	PieceInfo* pFoundPieceInfo = itfound->second;
	pFoundPieceInfo->SetRect(rect);
	return true;
}

const ImageInfo* ImagePieceDocument::AddImage(const wxString& strImageId, const wxString& strPath, wxBitmap* pImageBitmap)
{
	if (!pImageBitmap) return NULL;
	SetModifiedFlag();

	wxString strNewId = GenerateNewImageId(strImageId);
	ImageInfo* pImageInfo = new ImageInfo();
	pImageInfo->SetId(strNewId);
	pImageInfo->SetBitmap(pImageBitmap);
	pImageInfo->SetPath(strPath);
	m_ImageInfoMap.insert(std::make_pair(pImageInfo->GetId(), pImageInfo));

	m_bNeedUpdateImageIds = true;
	return pImageInfo;
}

bool ImagePieceDocument::RemoveImage(const wxString& strId)
{
	TM_IMAGE_INFO::iterator itfound = m_ImageInfoMap.find(strId);
	if (itfound == m_ImageInfoMap.end()) return false;
	SetModifiedFlag();

	ImageInfo* pImageInfo = (itfound->second);
	m_ImageInfoMap.erase(itfound);

	TV_PIECE_INFO vPieceInfo;
	EnumImagePieces(vPieceInfo, pImageInfo);
	for (TV_PIECE_INFO::iterator it = vPieceInfo.begin(); it != vPieceInfo.end(); ++it)
	{
		RemovePiece((*it)->GetId());
	}

	SAFE_DELETE(pImageInfo);
	return true;
}

const PieceInfo* ImagePieceDocument::AddPiece(const wxString& strId, const wxRect& rect, const ImageInfo* pImageInfo)
{
	if (!pImageInfo) return NULL;
	if (rect.width <= 0 || rect.height <= 0) return NULL;
	SetModifiedFlag();

	wxString strNewId = GenerateNewPieceId(strId);
	PieceInfo* pNewPieceInfo = new PieceInfo();
	pNewPieceInfo->SetId(strNewId);
	pNewPieceInfo->SetRect(rect);
	pNewPieceInfo->SetImageInfo(pImageInfo);
	m_PieceInfoMap.insert(std::make_pair(pNewPieceInfo->GetId(), pNewPieceInfo));

	m_bNeedUpdatePieceIds = true;
	return pNewPieceInfo;
}

bool ImagePieceDocument::RemovePiece(const wxString& strId)
{
	TM_PIECE_INFO::iterator itfound = m_PieceInfoMap.find(strId);
	if (itfound == m_PieceInfoMap.end()) return false;
	SetModifiedFlag();

	PieceInfo* pPieceInfo = (itfound->second);
	m_PieceInfoMap.erase(itfound);
	SAFE_DELETE(pPieceInfo);

	return true;
}

wxString ImagePieceDocument::GenerateNewImageId(const wxString& strId)
{
	wxString strNewId = strId;
	int index = 0;

	while (FindImageInfo(strNewId))
	{
		strNewId = wxString::Format("%s%d", strId, index++);
	}

	return strNewId;
}

wxString ImagePieceDocument::GenerateNewPieceId(const wxString& strId)
{
	wxString strNewId = strId;
	int index = 0;

	while (FindPieceInfo(strNewId))
	{
		strNewId = wxString::Format("%s%d", strId, index++);
	}

	return strNewId;
}

void ImagePieceDocument::UpdateImageArrayString()
{
	if (!m_bNeedUpdateImageIds) return;
	m_bNeedUpdateImageIds = false;

	int nIndex = 0;
	m_ImageIds.Clear();
	m_ImageIdsIndex.Clear();

	m_ImageIds.Add("null");
	m_ImageIdsIndex.Add(nIndex++);

	for (TM_IMAGE_INFO::iterator it = m_ImageInfoMap.begin(); it != m_ImageInfoMap.end(); ++it)
	{
		m_ImageIds.Add(it->first);
		m_ImageIdsIndex.Add(nIndex++);
	}
}

void ImagePieceDocument::UpdatePieceArrayString()
{
	if (!m_bNeedUpdatePieceIds) return;
	m_bNeedUpdatePieceIds = false;

	int nIndex = 0;
	m_PieceIds.Clear();
	m_PieceIdsIndex.Clear();

	m_PieceIds.Add("null");
	m_PieceIdsIndex.Add(nIndex++);

	for (TM_PIECE_INFO::iterator it = m_PieceInfoMap.begin(); it != m_PieceInfoMap.end(); ++it)
	{
		m_PieceIds.Add(it->first);
		m_PieceIdsIndex.Add(nIndex++);
	}
}
