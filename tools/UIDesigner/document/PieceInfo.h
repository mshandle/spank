/*!
 * \file PieceInfo.h
 * \date 2-13-2012 19:33:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __PIECEINFO_H__
#define __PIECEINFO_H__

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <tinyxml-2.6.2/tinyxml.h>
#include "ImageInfo.h"

class PieceInfo
{
public:
	PieceInfo();
	~PieceInfo();

	bool LoadFromXml(TiXmlElement* pElmPiece);
	bool SaveToXml(TiXmlElement* pElmPieceList);

	void SetId(const wxString& strId);
	const wxString& GetId() const;

	void SetImageInfo(ImageInfo* pImageInfo);
	ImageInfo* GetImageInfo();

	void SetRect(const wxRect& rect);
	const wxRect& GetRect() const;

	void SetTreeItemId(wxTreeItemId itemId);
	wxTreeItemId GetTreeItemId();

private:
	wxString m_strId;
	ImageInfo* m_pImageInfo;
	wxRect m_Rect;
	wxTreeItemId m_TreeItemId;

};
#endif // __PIECEINFO_H__
