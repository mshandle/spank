/*!
 * \file FileMgr_Impl.h
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FILEMGR_IMPL_H__
#define __FILEMGR_IMPL_H__

#include <IFileMgr.h>
#include "unzip/unzip.h"

class FileMgr_Impl : public IFileMgr
{
public:
	enum CONST_DEFINE
	{
		MAX_FILE_PATH = 260,
	};

public:
	FileMgr_Impl();
	virtual ~FileMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual StreamReader* LoadFile(const char* pszFileName);

private:
	unzFile m_pMainFile;

};
#endif // __FILEMGR_IMPL_H__
