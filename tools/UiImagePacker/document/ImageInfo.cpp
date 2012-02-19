/*!
 * \file ImageInfo.cpp
 * \date 2-13-2012 19:34:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImageInfo.h"
#include "ProjectDocument.h"
#include <wx/msgdlg.h>
#include "../ImagePackerFrame.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

ImageInfo::ImageInfo()
{
	m_pbmpImage = NULL;
	m_bLoaded = false;
	m_bIsModified = false;
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

bool ImageInfo::SaveImage()
{
	if (!m_bIsModified) return true;
	m_bIsModified = false;
	if (!m_pbmpImage) return true;

	wxString strFullPath = ProjectDocument::GetInstance().GetRootPath() + "/" + m_strPath;
	if (!m_pbmpImage->SaveFile(strFullPath, wxBITMAP_TYPE_PNG))
	{
		wxMessageDialog msg(&ImagePackerFrame::GetInstance(), wxString::Format("save image bitmap failed, path=%s", strFullPath));
		msg.ShowModal();
	}

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

bool ImageInfo::SetBitmap(wxBitmap* pBitmap)
{
	if (m_pbmpImage == pBitmap) return false;

	SAFE_DELETE(m_pbmpImage);
	m_pbmpImage = pBitmap;
	m_bIsModified = true;
	return true;
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

	// create new bitmap
	m_pbmpImage = new wxBitmap();

	// load bitmap from path
	wxString strFullPath = ProjectDocument::GetInstance().GetRootPath() + "/" + m_strPath;
	if (!m_pbmpImage->LoadFile(strFullPath, wxBITMAP_TYPE_ANY))
	{
		wxMessageDialog msg(&ImagePackerFrame::GetInstance(), wxString::Format("can not open file: %s", strFullPath));
		msg.ShowModal();
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
