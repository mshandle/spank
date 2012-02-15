/*!
 * \file ImageInfo.h
 * \date 2-13-2012 19:34:28
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGEINFO_H__
#define __IMAGEINFO_H__

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <tinyxml-2.6.2/tinyxml.h>

class ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();

	bool LoadFromXml(TiXmlElement* pElmImage);
	bool SaveToXml(TiXmlElement* pElmImageList);

	const wxString& GetId() const;
	const wxString& GetPath() const;

	wxBitmap* GetBitmap();

	void SetTreeItemId(wxTreeItemId itemId);
	wxTreeItemId GetTreeItemId();

private:
	bool LoadImageFromFile();

private:
	wxString m_strId;
	wxString m_strPath;
	wxBitmap* m_pbmpImage;
	bool m_bLoaded;
	wxTreeItemId m_TreeItemId;

};
#endif // __IMAGEINFO_H__
