/*!
 * \file ImageInfo.cpp
 * \date 2-13-2012 19:34:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImageInfo.h"
#include "ProjectDocument.h"

ImageInfo::ImageInfo()
{
	m_pbmpImage = NULL;
	m_bLoaded = false;
}

ImageInfo::~ImageInfo()
{
	if (m_pbmpImage)
	{
		delete m_pbmpImage;
		m_pbmpImage = NULL;
	}
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

const wxString& ImageInfo::GetId() const
{
	return m_strId;
}

const wxString& ImageInfo::GetPath() const
{
	return m_strPath;
}

wxBitmap* ImageInfo::GetBitmap()
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

	m_pbmpImage = new wxBitmap();
	if (!m_pbmpImage->LoadFile(ProjectDocument::GetInstance().GetRootPath() + m_strPath, wxBITMAP_TYPE_ANY))
	{
		delete m_pbmpImage;
		m_pbmpImage = NULL;
		return false;
	}

	return true;
}

void ImageInfo::SetTreeItemId(wxTreeItemId itemId)
{
	m_TreeItemId = itemId;
}

wxTreeItemId ImageInfo::GetTreeItemId()
{
	return m_TreeItemId;
}