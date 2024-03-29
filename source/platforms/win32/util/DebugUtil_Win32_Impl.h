/*!
 * \file DebugUtil_Win32_Impl.h
 * \date 7-20-2011 18:06:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DEBUGUTIL_WIN32_IMPL_H__
#define __DEBUGUTIL_WIN32_IMPL_H__

#include <util/IDebugUtil.h>
#include <stdio.h>
#include <windows.h>

class DebugUtil_Win32_Impl : public IDebugUtil
{
public:
	enum CONST_DEFINE
	{
		MAX_BUFFER_SIZE = 1024,
	};

public:
	DECLARE_RTTI(DebugUtil_Win32_Impl, IDebugUtil);

	DebugUtil_Win32_Impl();
	virtual ~DebugUtil_Win32_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Debug(const char* format, ...);
	virtual void Info(const char* format, ...);
	virtual void Error(const char* format, ...);

private:
	void OutputLog(const char* pszTag, const char* pszLog);

private:
	FILE* m_pLogFile;
	HANDLE m_hConsole;

};

#endif // __DEBUGUTIL_WIN32_IMPL_H__
