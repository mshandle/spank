/*!
 * \file BitmapStyleDocument.h
 * \date 2-14-2012 13:49:33
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BITMAPSTYLEDOCUMENT_H__
#define __BITMAPSTYLEDOCUMENT_H__

#include "DocumentBase.h"
#include "BitmapStyle.h"
#include <map>

class BitmapStyleDocument : public DocumentBase
{
public:
	typedef std::map<wxString, BitmapStyle*> TM_BITMAP_STYLE;

public:
	virtual ~BitmapStyleDocument();
	static BitmapStyleDocument& GetInstance();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual void Reset();
	virtual const wxString& GetFilePath() const;

	const BitmapStyle* FindBitmapStyle(const wxString& strId);
	const TM_BITMAP_STYLE& GetBitmapStyleMap();

	bool RenameBitmapStyleId(const BitmapStyle* pBitmapStyle, const wxString& strNewId);
	bool SetStatePiece(const BitmapStyle* pBitmapStyle, const PieceInfo* pPieceInfo, IStyle::STYLE_STATE eState);

	const BitmapStyle* AddBitmapStyle(const wxString& strId);

protected:
	BitmapStyleDocument();
	BitmapStyle* InternalFindBitmapStyle(const wxString& strId);

	wxString GenerateNewBitmapStyleId(const wxString& strId);

private:
	TM_BITMAP_STYLE m_BitmapStyleMap;
	wxString m_strFile;

};
#endif // __BITMAPSTYLEDOCUMENT_H__
