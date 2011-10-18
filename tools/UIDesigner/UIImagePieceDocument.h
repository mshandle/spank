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

class UIImagePieceDocument : public UIDocumentBase
{
public:
	typedef struct IMAGE_INFO_tag
	{
		int nID;
		wxString strFile;
	} IMAGE_INFO;
	
	typedef std::map<int, IMAGE_INFO> TM_IMAGE_INFO;

	typedef struct PIECE_INFO_tag
	{
		wxString strID;
		int nImageID;
		wxRect rect;
	} PIECE_INFO;

	typedef std::map<wxString, PIECE_INFO> TM_PIECE_INFO;

public:
	UIImagePieceDocument();
	virtual ~UIImagePieceDocument();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual bool NewFile (const wxString& strFile);
	virtual const wxString& GetFileName() const;

	TM_IMAGE_INFO& GetImageMap();
	const wxString& FindImage(int nID) const ;
	void AddPieceInfo(const PIECE_INFO& PieceInfo);
	void AddImageInfo(const IMAGE_INFO& ImageInfo);
	TM_PIECE_INFO& GetPieceInfoMap();
	int GetImageMapKeyValue(const wxString& strValue);
	 PIECE_INFO* FindPieceInfo(const wxString& strID) ;
	
	void UpdateImagePiece(const PIECE_INFO& pieceInfo);
	void Clear();
private:
	TM_IMAGE_INFO m_ImageMap;
	TM_PIECE_INFO m_PieceInfoMap;
	wxString m_strFile;

};
#endif // __UIIMAGEPIECEDOCUMENT_H__
