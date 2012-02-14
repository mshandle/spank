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

	BitmapStyle* FindBitmapStyle(const wxString& strId);
	TM_BITMAP_STYLE& GetBitmapStyleMap();

protected:
	BitmapStyleDocument();

private:
	TM_BITMAP_STYLE m_BitmapStyleMap;
	wxString m_strFile;

};
#endif // __BITMAPSTYLEDOCUMENT_H__
