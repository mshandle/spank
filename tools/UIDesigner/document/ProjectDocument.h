/*!
 * \file ProjectDocument.h
 * \date 2-14-2012 13:21:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __PROJECTDOCUMENT_H__
#define __PROJECTDOCUMENT_H__

#include "DocumentBase.h"

class ProjectDocument: public DocumentBase
{
public:
	virtual ~ProjectDocument();

	static ProjectDocument& GetInstance();

	virtual bool OpenFile(const wxString& strFile);
	virtual bool SaveFile(const wxString& strFile);
	virtual void Reset();
	virtual const wxString& GetFilePath() const;

	const wxString& GetRootPath() const;

protected:
	ProjectDocument();

private:
	wxString m_strRootPath;
	wxString m_strFile;

};

#endif // __PROJECTDOCUMENT_H__
