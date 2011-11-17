/*!
 * \file StreamWriter.cpp
 * \date 18-05-2011 22:58:04
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <StreamWriter.h>
#include <memory>

StreamWriter::StreamWriter()
{
	m_pBuffer = NULL;
	m_nSize = 0;
	m_nPos = 0;
	m_bOK = true;
}

StreamWriter::~StreamWriter()
{
	SAFE_DELETE_ARRAY(m_pBuffer);
}

bool StreamWriter::Write(const void* pData, int nSize)
{
	if (!pData) return false;
	if (nSize <= 0) return true;

	if (m_nPos + nSize > m_nSize)
	{
		if (!Expend(m_nPos + nSize)) return false;
	}

	memcpy(&m_pBuffer[m_nPos], pData, nSize);
	m_nPos += nSize;
	return true;
}

bool StreamWriter::Expend(int nRequireSize)
{
	int nNewSize = ((nRequireSize/BLOCK_ALIGN)+1) * BLOCK_ALIGN;
	char* pNewBuffer = new char[nNewSize];
	if (!pNewBuffer) return false;

	if (m_pBuffer)
	{
		memcpy(pNewBuffer, m_pBuffer, m_nSize);
		delete[] m_pBuffer;
	}

	m_pBuffer = pNewBuffer;
	m_nSize = nNewSize;
	return true;
}

void StreamWriter::Reset()
{
	m_nPos = 0;
}

const void* StreamWriter::GetBuffer()
{
	return m_pBuffer;
}

int StreamWriter::GetBufferSize()
{
	return m_nPos;
}
