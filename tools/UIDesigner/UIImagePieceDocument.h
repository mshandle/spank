/*!
 * \file UIImagePieceDocument.h
 * \date 11-09-2011 08:21:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIIMAGEPIECEDOCUMENT_H__
#define __UIIMAGEPIECEDOCUMENT_H__

#include "UIDocumentBase.h"
#include <wx/gdicmn.h>
#include <map>
#include "ImageInfo.h"
#include "PieceInfo.h"

class UIImagePieceDocument : public UIDocumentBase
{
public:
	typedef std::map<wxString, ImageInfo*> TM_IMAGE_INFO;
	typedef std::map<wxString, PieceInfo*> TM_PIECE_INFO;

public:
	UIImagePieceDocument();
	virtual ~UIImagePieceDocument();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual bool NewFile(const wxString& strFile);
	virtual const wxString& GetFileName() const;

	ImageInfo* FindImageInfo(const wxString& strId);
	PieceInfo* FindPieceInfo(const wxString& strId);

	const TM_IMAGE_INFO& GetImageInfoMap() const;
	const TM_PIECE_INFO& GetPieceInfoMap() const;

	void Clear();

private:
	TM_IMAGE_INFO m_ImageInfoMap;
	TM_PIECE_INFO m_PieceInfoMap;
	wxString m_strFile;

};
#endif // __UIIMAGEPIECEDOCUMENT_H__
