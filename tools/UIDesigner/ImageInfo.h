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
#include <tinyxml-2.6.2/tinyxml.h>

class ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();

	bool LoadFromXml(TiXmlElement* pElmImage);

	const wxString& GetId() const;
	const wxString& GetPath() const;

	wxBitmap* GetImage();

private:
	bool LoadImageFromFile();

private:
	wxString m_strId;
	wxString m_strPath;
	wxBitmap* m_pbmpImage;
	bool m_bLoaded;

};
#endif // __IMAGEINFO_H__
