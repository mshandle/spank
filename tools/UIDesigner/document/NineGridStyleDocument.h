/*!
 * \file NineGridStyleDocument.h
 * \date 2-14-2012 15:24:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NINEGRIDSTYLEDOCUMENT_H__
#define __NINEGRIDSTYLEDOCUMENT_H__

#include "DocumentBase.h"
#include "NineGridStyle.h"
#include <map>

class NineGridStyleDocument : public DocumentBase
{
public:
	typedef std::map<wxString, NineGridStyle*> TM_NINE_GRID_STYLE;

public:
	virtual ~NineGridStyleDocument();
	static NineGridStyleDocument& GetInstance();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual void Reset();
	virtual const wxString& GetFilePath() const;

	NineGridStyle* FindNineGridStyle(const wxString& strId);
	TM_NINE_GRID_STYLE& GetNineGridStyleMap();

protected:
	NineGridStyleDocument();

private:
	TM_NINE_GRID_STYLE m_NineGridStyleMap;
	wxString m_strFile;

};
#endif // __NINEGRIDSTYLEDOCUMENT_H__
