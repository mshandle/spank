/*!
 * \file ImageInfo.cpp
 * \date 2-13-2012 19:34:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImageInfo.h"

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
	m_strPath = pElmImage->Attribute("file");

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

wxBitmap* ImageInfo::GetImage()
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
	if (!m_pbmpImage->LoadFile("ui/" + m_strPath, wxBITMAP_TYPE_ANY))
	{
		delete m_pbmpImage;
		m_pbmpImage = NULL;
		return false;
	}

	return true;
}
