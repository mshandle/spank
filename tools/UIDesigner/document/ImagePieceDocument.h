/*!
 * \file ImagePieceDocument.h
 * \date 2-14-2012 1:23:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGEPIECEDOCUMENT_H__
#define __IMAGEPIECEDOCUMENT_H__

#include "DocumentBase.h"
#include <wx/gdicmn.h>
#include <map>
#include "ImageInfo.h"
#include "PieceInfo.h"

class ImagePieceDocument : public DocumentBase
{
public:
	typedef std::map<wxString, ImageInfo*> TM_IMAGE_INFO;
	typedef std::map<wxString, PieceInfo*> TM_PIECE_INFO;

public:
	virtual ~ImagePieceDocument();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual void Reset();
	virtual const wxString& GetFilePath() const;

	static ImagePieceDocument& GetInstance();

	ImageInfo* FindImageInfo(const wxString& strId);
	PieceInfo* FindPieceInfo(const wxString& strId);
	PieceInfo* FindPieceInfoUnderPoint(const wxPoint& pos, const ImageInfo* pImageInfo);

	TM_IMAGE_INFO& GetImageInfoMap();
	TM_PIECE_INFO& GetPieceInfoMap();

protected:
	ImagePieceDocument();

private:
	TM_IMAGE_INFO m_ImageInfoMap;
	TM_PIECE_INFO m_PieceInfoMap;
	wxString m_strFile;

};
#endif // __IMAGEPIECEDOCUMENT_H__
