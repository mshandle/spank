/*!
 * \file DocumentBase.h
 * \date 2-14-2012 1:22:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DOCUMENTBASE_H__
#define __DOCUMENTBASE_H__

#include <wx/string.h>

class DocumentBase
{
public:
	DocumentBase();
	virtual ~DocumentBase();

	virtual bool OpenFile(const wxString& strFile) = 0;
	virtual bool SaveFile(const wxString& strFile) = 0;
	virtual void Reset() = 0;
	virtual const wxString& GetFilePath() const = 0;

	void SetModifiedFlag();
	void ClearModifiedFlag();
	bool isModified() const;

private:
	bool m_bModifiedFlag;

};
#endif // __DOCUMENTBASE_H__
