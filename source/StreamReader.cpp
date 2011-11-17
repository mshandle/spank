/*!
 * \file StreamReader.cpp
 * \date 18-05-2011 22:36:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <StreamReader.h>
#include <memory>

StreamReader::StreamReader(const void* pBuffer, int nBufferSize, bool bManageBuffer /* = false */)
{
	m_pBuffer = (const char*)pBuffer;
	m_nBufferSize = nBufferSize;
	m_bManageBuffer = bManageBuffer;
	m_nReadPos = 0;
	m_bOK = (m_pBuffer != NULL && m_nBufferSize > 0);
}

StreamReader::~StreamReader()
{
	if (m_bManageBuffer)
	{
		SAFE_DELETE_ARRAY(m_pBuffer);
	}
}

bool StreamReader::Read(void* pDataOut, int nSize)
{
	if (!pDataOut || nSize + m_nReadPos > m_nBufferSize) return false;

	const void* pBuffer = GetBuffer();
	memcpy(pDataOut, pBuffer, nSize);
	m_nReadPos += nSize;

	return true;
}

bool StreamReader::Skip(int nSize)
{
	if (nSize + m_nReadPos > m_nBufferSize) return false;
	m_nReadPos += nSize;
	return true;
}

void StreamReader::Reset()
{
	m_nReadPos = 0;
}

const void* StreamReader::GetBuffer()
{
	const char* pBuffer = m_pBuffer;
	pBuffer += m_nReadPos;
	return pBuffer;
}

int StreamReader::GetSize()
{
	return m_nBufferSize - m_nReadPos;
}
