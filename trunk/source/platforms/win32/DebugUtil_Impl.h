/*!
 * \file DebugUtil_Impl.h
 * \date 7-20-2011 18:06:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DEBUGUTIL_IMPL_H__
#define __DEBUGUTIL_IMPL_H__

#include <IDebugUtil.h>
#include <stdio.h>

class DebugUtil_Impl : public IDebugUtil
{
public:
	enum CONST_DEFINE
	{
		MAX_BUFFER_SIZE = 1024,
	};

public:
	virtual bool Initialize();
	virtual void Terminate();

	virtual void Debug(const char* format, ...);
	virtual void Info(const char* format, ...);
	virtual void Error(const char* format, ...);

private:
	FILE* m_pLogFile;

};

#endif // __DEBUGUTIL_IMPL_H__
