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
#include <tinyxml-2.6.2/tinyxml.h>

class PieceInfo
{
public:
	PieceInfo();
	~PieceInfo();

	bool LoadFromXml(TiXmlElement* pElmPiece);

	void SetId(const wxString& strId);
	const wxString& GetId() const;

	void SetImageId(const wxString& strImageId);
	const wxString& GetImageId() const;

	void SetRect(const wxRect& rect);
	const wxRect& GetRect() const;

private:
	wxString m_strId;
	wxString m_strImageId;
	wxRect m_Rect;

};
#endif // __PIECEINFO_H__
