/*!
 * \file ProjectDocument.cpp
 * \date 2-14-2012 13:21:35
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ProjectDocument.h"
#include "ImagePieceDocument.h"
#include "BitmapStyleDocument.h"
#include "NineGridStyleDocument.h"
#include "ColorStyleDocument.h"
#include "ClipBitmapStyleDocument.h"
#include <tinyxml-2.6.2/tinyxml.h>

ProjectDocument::ProjectDocument()
{
	// TODO: 
}

ProjectDocument::~ProjectDocument()
{
	// TODO: 
}

ProjectDocument& ProjectDocument::GetInstance()
{
	static ProjectDocument s_ProjectDocument;
	return s_ProjectDocument;
}

bool ProjectDocument::OpenFile(const wxString& strFile)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(strFile)) return false;

	Reset();

	m_strFile = strFile;

	TiXmlElement* pElmUdProject = doc.RootElement();
	if (!pElmUdProject || strcmp(pElmUdProject->Value(), "ud_project") != 0) return false;

	const char* pszRootPath = pElmUdProject->Attribute("root_path");
	if (pszRootPath)
	{
		m_strRootPath = pszRootPath;
	}
	else
	{
		m_strRootPath.clear();
	}

	TiXmlElement* pElmImagePiece = pElmUdProject->FirstChildElement("image_piece");
	if (!pElmImagePiece) return false;
	ImagePieceDocument::GetInstance().OpenFile(m_strRootPath + pElmImagePiece->Attribute("path"));

	TiXmlElement* pElmBitmapStyle = pElmUdProject->FirstChildElement("bitmap_style");
	if (!pElmBitmapStyle) return false;
	BitmapStyleDocument::GetInstance().OpenFile(m_strRootPath + pElmBitmapStyle->Attribute("path"));

	TiXmlElement* pElmNineGridStyle = pElmUdProject->FirstChildElement("nine_grid_style");
	if (!pElmNineGridStyle) return false;
	NineGridStyleDocument::GetInstance().OpenFile(m_strRootPath + pElmNineGridStyle->Attribute("path"));

	TiXmlElement* pElmColorStyle = pElmUdProject->FirstChildElement("color_style");
	if (!pElmColorStyle) return false;
	ColorStyleDocument::GetInstance().OpenFile(m_strRootPath + pElmColorStyle->Attribute("path"));

	TiXmlElement* pElmClipBitmapStyle = pElmUdProject->FirstChildElement("clip_bitmap_style");
	if (!pElmClipBitmapStyle) return false;
	ClipBitmapStyleDocument::GetInstance().OpenFile(m_strRootPath + pElmClipBitmapStyle->Attribute("path"));

	return true;
}

bool ProjectDocument::SaveFile(const wxString& strFile)
{
	ImagePieceDocument::GetInstance().SaveFile(ImagePieceDocument::GetInstance().GetFilePath());
	BitmapStyleDocument::GetInstance().SaveFile(BitmapStyleDocument::GetInstance().GetFilePath());
	NineGridStyleDocument::GetInstance().SaveFile(NineGridStyleDocument::GetInstance().GetFilePath());
	ColorStyleDocument::GetInstance().SaveFile(ColorStyleDocument::GetInstance().GetFilePath());
	ClipBitmapStyleDocument::GetInstance().SaveFile(ClipBitmapStyleDocument::GetInstance().GetFilePath());

	return true;
}

void ProjectDocument::Reset()
{
	// TODO: 
}

const wxString& ProjectDocument::GetFilePath() const
{
	return m_strFile;
}

const wxString& ProjectDocument::GetRootPath() const
{
	return m_strRootPath;
}
