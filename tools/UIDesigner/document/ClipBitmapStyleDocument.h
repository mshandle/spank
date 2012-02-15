/*!
 * \file ClipBitmapStyleDocument.h
 * \date 2-14-2012 16:47:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CLIPBITMAPSTYLEDOCUMENT_H__
#define __CLIPBITMAPSTYLEDOCUMENT_H__

#include "DocumentBase.h"
#include "ClipBitmapStyle.h"
#include <map>

class ClipBitmapStyleDocument : public DocumentBase
{
public:
	typedef std::map<wxString, ClipBitmapStyle*> TM_CLIP_BITMAP_STYLE;

public:
	virtual ~ClipBitmapStyleDocument();
	static ClipBitmapStyleDocument& GetInstance();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual void Reset();
	virtual const wxString& GetFilePath() const;

	ClipBitmapStyle* FindClipBitmapStyle(const wxString& strId);
	TM_CLIP_BITMAP_STYLE& GetClipBitmapStyleMap();

	bool RenameClipBitmapStyleId(const ClipBitmapStyle* pClipBitmapStyle, const wxString& strNewId);
	bool SetStatePiece(const ClipBitmapStyle* pClipBitmapStyle, PieceInfo* pPieceInfo, IStyle::STYLE_STATE eState);

protected:
	ClipBitmapStyleDocument();

private:
	TM_CLIP_BITMAP_STYLE m_ClipBitmapStyleMap;
	wxString m_strFile;

};
#endif // __CLIPBITMAPSTYLEDOCUMENT_H__
