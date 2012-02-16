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

	void SetId(const wxString& strId);
	const wxString& GetId() const;

	void SetPath(const wxString& strPath);
	const wxString& GetPath() const;

	void SetBitmap(wxBitmap* pBitmap);
	const wxBitmap* GetBitmap();

	void SetTreeItemId(const wxTreeItemId& itemId);
	const wxTreeItemId& GetTreeItemId() const;

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
