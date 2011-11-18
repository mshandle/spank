/*!
 * \file StringUtil.cpp
 * \date 14-08-2011 11:22:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <util/StringUtil.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void StringUtil::ZeroMemory(void* pBuffer, int nSize)
{
	memset(pBuffer, 0, nSize);
}

bool StringUtil::CopyString(char* pszBufferOut, int nBufferSize, const char* pszIn)
{
	if (!pszBufferOut || !pszIn || nBufferSize <= 0) return false;

	while ((--nBufferSize) > 0 && *pszIn)
	{
		*(pszBufferOut++) = (*pszIn++);
	}

	*pszBufferOut = '\0';
	return true;
}

int StringUtil::StringLength(const char* pszString)
{
	if (!pszString) return 0;

	const char* pszCurr = pszString;
	while (*pszCurr++);

	return pszCurr - pszString - 1;
}

bool StringUtil::IsEqual(const char* psz1, const char* psz2)
{
	if (psz1 == psz2) return true;
	if (psz1 == NULL || psz2 == NULL) return false;
	if (strcmp(psz1, psz2) != 0) return false;
	return true;
}

int StringUtil::Utf8ToUnicode(ushort* pUnicodeOut, int nUnicodeLength, const char* pszUtf8)
{
	//        unicode                   utf-8
	// 
	// 0000 0000-0000 007F | 0xxxxxxx
	// 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
	// 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
	// ...																	// 以下不在考虑范围内 ...
	// 0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx			// not implement.
	// ...
	// 

	if (!pszUtf8) return 0;

	int nUtf8Length = strlen(pszUtf8);
	int nFinalLength = 0;
	int nUtf8Index = 0;
	int nUnicodeIndex = 0;

	if (pUnicodeOut == NULL)
	{
		while (nUtf8Index < nUtf8Length)
		{
			if ((pszUtf8[nUtf8Index] & 0xE0) == 0xC0)					// 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
			{
				nUtf8Index += 2;
			}
			else if ((pszUtf8[nUtf8Index] & 0xF0) == 0xE0)				// 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
			{
				nUtf8Index += 3;
			}
			else														// 0000 0000-0000 007F | 0xxxxxxx
			{
				nUtf8Index += 1;
			}

			++nUnicodeIndex;
		}

		nFinalLength = nUnicodeIndex;
	}
	else
	{
		while (nUtf8Index < nUtf8Length)
		{
			if ((pszUtf8[nUtf8Index] & 0xE0) == 0xC0)					// 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
			{
				pUnicodeOut[nUnicodeIndex++] = 
					(((ushort)(pszUtf8[nUtf8Index] & 0x1F)) << 6)
					| (pszUtf8[nUtf8Index+1] & 0x3F);

				nUtf8Index += 2;
			}
			else if ((pszUtf8[nUtf8Index] & 0xF0) == 0xE0)				// 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
			{
				pUnicodeOut[nUnicodeIndex++] = 
					(((ushort)(pszUtf8[nUtf8Index] & 0x0F)) << 12)
					| (((ushort)(pszUtf8[nUtf8Index+1] & 0x3F)) << 6)
					| (pszUtf8[nUtf8Index+2] & 0x3F);

				nUtf8Index += 3;
			}
			else														// 0000 0000-0000 007F | 0xxxxxxx
			{
				pUnicodeOut[nUnicodeIndex++] = pszUtf8[nUtf8Index++];
			}
		}

		nFinalLength = nUnicodeIndex;
		if (nFinalLength >= nUnicodeLength) nFinalLength = nUnicodeLength - 1;

		pUnicodeOut[nFinalLength] = 0;
	}

	return nFinalLength;
}

bool StringUtil::Format(char* pszBuffer, int nBufferSize, const char* pszFormat, ...)
{
	va_list marker;
	va_start(marker, pszFormat);

	int nLength = vsnprintf(pszBuffer, nBufferSize, pszFormat, marker);
	va_end(marker);

	return true;
}
