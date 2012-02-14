/*!
 * \file ColorStyleDocument.h
 * \date 2-14-2012 16:53:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __COLORSTYLEDOCUMENT_H__
#define __COLORSTYLEDOCUMENT_H__

#include "DocumentBase.h"
#include "ColorStyle.h"
#include <map>

class ColorStyleDocument : public DocumentBase
{
public:
	typedef std::map<wxString, ColorStyle*> TM_COLOR_STYLE;

public:
	virtual ~ColorStyleDocument();
	static ColorStyleDocument& GetInstance();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual void Reset();
	virtual const wxString& GetFilePath() const;

	ColorStyle* FindColorStyle(const wxString& strId);
	TM_COLOR_STYLE& GetColorStyleMap();

protected:
	ColorStyleDocument();

private:
	TM_COLOR_STYLE m_ColorStyleMap;
	wxString m_strFile;

};
#endif // __COLORSTYLEDOCUMENT_H__
