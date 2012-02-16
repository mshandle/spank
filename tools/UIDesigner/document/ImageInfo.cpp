/*!
 * \file ImageInfo.cpp
 * \date 2-13-2012 19:34:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImageInfo.h"
#include "ProjectDocument.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

ImageInfo::ImageInfo()
{
	m_pbmpImage = NULL;
	m_bLoaded = false;
}

ImageInfo::~ImageInfo()
{
	SAFE_DELETE(m_pbmpImage);
}

bool ImageInfo::LoadFromXml(TiXmlElement* pElmImage)
{
	if (!pElmImage) return false;

	m_strId = pElmImage->Attribute("id");
	m_strPath = pElmImage->Attribute("path");

	return true;
}

bool ImageInfo::SaveToXml(TiXmlElement* pElmImageList)
{
	TiXmlElement* pElmImage = new TiXmlElement("Image");
	pElmImage->SetAttribute("id", m_strId);
	pElmImage->SetAttribute("path", m_strPath);
	pElmImageList->LinkEndChild(pElmImage);
	return true;
}

void ImageInfo::SetId(const wxString& strId)
{
	m_strId = strId;
}

const wxString& ImageInfo::GetId() const
{
	return m_strId;
}

void ImageInfo::SetPath(const wxString& strPath)
{
	m_strPath = strPath;
}

const wxString& ImageInfo::GetPath() const
{
	return m_strPath;
}

void ImageInfo::SetBitmap(wxBitmap* pBitmap)
{
	m_pbmpImage = pBitmap;
}

const wxBitmap* ImageInfo::GetBitmap()
{
	if (!m_pbmpImage && !m_bLoaded)
	{
		LoadImageFromFile();
		m_bLoaded = true;
	}

	return m_pbmpImage;
}

bool ImageInfo::LoadImageFromFile()
{
	if (m_pbmpImage) return false;

	SAFE_DELETE(m_pbmpImage);

	m_pbmpImage = new wxBitmap();
	if (!m_pbmpImage->LoadFile(ProjectDocument::GetInstance().GetRootDir() + "/" + m_strPath, wxBITMAP_TYPE_ANY))
	{
		SAFE_DELETE(m_pbmpImage);
		return false;
	}

	return true;
}

void ImageInfo::SetTreeItemId(const wxTreeItemId& itemId)
{
	m_TreeItemId = itemId;
}

const wxTreeItemId& ImageInfo::GetTreeItemId() const
{
	return m_TreeItemId;
}
