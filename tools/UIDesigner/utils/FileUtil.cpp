/*!
 * \file FileUtil.cpp
 * \date 2-13-2012 13:21:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil.h"

void FileUtil::FormatDir(wxString& strDirInOut)
{
	while (strDirInOut.rbegin() != strDirInOut.rend())
	{
		char ch = (*strDirInOut.rbegin());
		if (ch == '\\' || ch == '/')
		{
			strDirInOut.erase(strDirInOut.length()-1, 1);
		}
		else
		{
			break;
		}
	}

	strDirInOut.Replace("\\", "/");
}

wxString FileUtil::GetFileName(const wxString& strPath)
{
	int nStartPos = 0;
	for (int i = (int)strPath.length()-1; i >= 0; --i)
	{
		if (strPath[i] == '\\' || strPath[i] == '/')
		{
			nStartPos = i;
			break;
		}
	}

	int nEndPos = nStartPos;
	for (; nEndPos < (int)strPath.length(); ++nEndPos)
	{
		if (strPath[nEndPos] == '.') break;
	}

	return strPath.SubString(nStartPos+1, nEndPos-1);
}

void FileUtil::FormatId(wxString& strId)
{
	strId = strId.Lower();
	for (int i = 0; i < (int)strId.length(); ++i)
	{
		if ((strId[i] >= 'a' && strId[i] <= 'z')
			|| (strId[i] >= '0' && strId[i] <= '9'))
		{
			// TODO: 
		}
		else
		{
			strId[i] = '_';
		}
	}
}
