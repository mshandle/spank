/*!
 * \file DebugUtil_Impl.cpp
 * \date 7-20-2011 16:47:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DebugUtil_Impl.h"
#include <stdarg.h>

IDebugUtil& IDebugUtil::GetInstance()
{
	static DebugUtil_Impl s_DebugUtil_Impl;
	return s_DebugUtil_Impl;
}

bool DebugUtil_Impl::Initialize()
{
	m_pLogFile = NULL;
	fopen_s(&m_pLogFile, "log.txt", "w");
	if (!m_pLogFile) return false;

	return true;
}

void DebugUtil_Impl::Terminate()
{
	if (m_pLogFile)
	{
		fclose(m_pLogFile);
		m_pLogFile = NULL;
	}
}

void DebugUtil_Impl::Debug(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[MAX_BUFFER_SIZE];
	vsprintf_s(szOut, MAX_BUFFER_SIZE, format, marker);
	fprintf(m_pLogFile, "DEBUG: %s\n", szOut);

	va_end(marker);
}

void DebugUtil_Impl::Info(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[MAX_BUFFER_SIZE];
	vsprintf_s(szOut, MAX_BUFFER_SIZE, format, marker);
	fprintf(m_pLogFile, "INFO: %s\n", szOut);

	va_end(marker);
}

void DebugUtil_Impl::Error(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[MAX_BUFFER_SIZE];
	vsprintf_s(szOut, MAX_BUFFER_SIZE, format, marker);
	fprintf(m_pLogFile, "ERROR: %s\n", szOut);

	va_end(marker);
}
