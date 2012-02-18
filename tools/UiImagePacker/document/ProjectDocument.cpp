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
#include "../utils/FileUtil.h"
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
	SetFilePath(strFile);

	TiXmlElement* pElmUdProject = doc.RootElement();
	if (!pElmUdProject || strcmp(pElmUdProject->Value(), "ud_project") != 0) return false;

	const char* pszRootPath = pElmUdProject->Attribute("root_dir");
	if (pszRootPath)
	{
		m_strRootDir = pszRootPath;
		FileUtil::FormatDir(m_strRootDir);
	}
	else
	{
		m_strRootDir.clear();
	}

	TiXmlElement* pElmImagePiece = pElmUdProject->FirstChildElement("image_piece");
	if (!pElmImagePiece) return false;
	m_strImagePieceFilePath = (m_strProjectDir + "/" + pElmImagePiece->Attribute("path"));

	TiXmlElement* pElmBitmapStyle = pElmUdProject->FirstChildElement("bitmap_style");
	if (!pElmBitmapStyle) return false;
	m_strBitmapStyleFilePath = (m_strProjectDir + "/" + pElmBitmapStyle->Attribute("path"));

	TiXmlElement* pElmNineGridStyle = pElmUdProject->FirstChildElement("nine_grid_style");
	if (!pElmNineGridStyle) return false;
	m_strNineGridStyleFilePath = (m_strProjectDir + "/" + pElmNineGridStyle->Attribute("path"));

	TiXmlElement* pElmColorStyle = pElmUdProject->FirstChildElement("color_style");
	if (!pElmColorStyle) return false;
	m_strColorStyleFilePath = (m_strProjectDir + "/" + pElmColorStyle->Attribute("path"));

	TiXmlElement* pElmClipBitmapStyle = pElmUdProject->FirstChildElement("clip_bitmap_style");
	if (!pElmClipBitmapStyle) return false;
	m_strClipBitmapStyleFilePath = (m_strProjectDir + "/" + pElmClipBitmapStyle->Attribute("path"));

	return true;
}

bool ProjectDocument::SaveFile(const wxString& strFile)
{
	if (!IsModified()) return true;
	ClearModifiedFlag();

	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
	doc.LinkEndChild(pDecl);

	TiXmlElement* pElmUdProject = new TiXmlElement("ud_project");
	doc.LinkEndChild(pElmUdProject);
	pElmUdProject->SetAttribute("root_dir", m_strRootDir);

	TiXmlElement* pElmImagePiece = new TiXmlElement("image_piece");
	pElmUdProject->LinkEndChild(pElmImagePiece);
	pElmImagePiece->SetAttribute("path", FileUtil::RemoveRootDir(ImagePieceDocument::GetInstance().GetFilePath(), m_strProjectDir + "/"));

	TiXmlElement* pElmBitmapStyle = pElmUdProject->FirstChildElement("bitmap_style");
	pElmUdProject->LinkEndChild(pElmBitmapStyle);
	pElmBitmapStyle->SetAttribute("path", FileUtil::RemoveRootDir(BitmapStyleDocument::GetInstance().GetFilePath(), m_strProjectDir + "/"));

	TiXmlElement* pElmNineGridStyle = pElmUdProject->FirstChildElement("nine_grid_style");
	pElmUdProject->LinkEndChild(pElmNineGridStyle);
	pElmNineGridStyle->SetAttribute("path", FileUtil::RemoveRootDir(NineGridStyleDocument::GetInstance().GetFilePath(), m_strProjectDir + "/"));

	TiXmlElement* pElmColorStyle = pElmUdProject->FirstChildElement("color_style");
	pElmUdProject->LinkEndChild(pElmColorStyle);
	pElmColorStyle->SetAttribute("path", FileUtil::RemoveRootDir(ColorStyleDocument::GetInstance().GetFilePath(), m_strProjectDir + "/"));

	TiXmlElement* pElmClipBitmapStyle = pElmUdProject->FirstChildElement("clip_bitmap_style");
	pElmUdProject->LinkEndChild(pElmClipBitmapStyle);
	pElmClipBitmapStyle->SetAttribute("path", FileUtil::RemoveRootDir(ClipBitmapStyleDocument::GetInstance().GetFilePath(), m_strProjectDir + "/"));

	return doc.SaveFile(strFile);
}

void ProjectDocument::Reset()
{
	ClearModifiedFlag();
}

const wxString& ProjectDocument::GetRootDir() const
{
	return m_strRootDir;
}

wxString ProjectDocument::GetRootPath() const
{
	return m_strProjectDir + "/" + m_strRootDir;
}

void ProjectDocument::SetProjectDir(const wxString& strProjectDir)
{
	m_strProjectDir = strProjectDir;
	FileUtil::FormatDir(m_strProjectDir);
}

const wxString& ProjectDocument::GetProjectDir() const
{
	return m_strProjectDir;
}

bool ProjectDocument::SetImagePieceFilePath(const wxString& strPath)
{
	m_strImagePieceFilePath = strPath;
	return true;
}

const wxString& ProjectDocument::GetImagePieceFilePath() const
{
	return m_strImagePieceFilePath;
}

bool ProjectDocument::SetBitmapStyleFilePath(const wxString& strPath)
{
	m_strBitmapStyleFilePath = strPath;
	return true;
}

const wxString& ProjectDocument::GetBitmapStyleFilePath() const
{
	return m_strBitmapStyleFilePath;
}

bool ProjectDocument::SetNineGridStyleFilePath(const wxString& strPath)
{
	m_strNineGridStyleFilePath = strPath;
	return true;
}

const wxString& ProjectDocument::GetNineGridStyleFilePath() const
{
	return m_strNineGridStyleFilePath;
}

bool ProjectDocument::SetColorStyleFilePath(const wxString& strPath)
{
	m_strColorStyleFilePath = strPath;
	return true;
}

const wxString& ProjectDocument::GetColorStyleFilePath() const
{
	return m_strColorStyleFilePath;
}

bool ProjectDocument::SetClipBitmapStyleFilePath(const wxString& strPath)
{
	m_strClipBitmapStyleFilePath = strPath;
	return true;
}

const wxString& ProjectDocument::GetClipBitmapStyleFilePath() const
{
	return m_strClipBitmapStyleFilePath;
}
