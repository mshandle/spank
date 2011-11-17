/*!
 * \file StreamReader.h
 * \date 18-05-2011 22:31:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __STREAMREADER_H__
#define __STREAMREADER_H__

#include "IObject.h"

class StreamReader : public IObject
{
public:
	DECLARE_RTTI(StreamReader, IObject);

	StreamReader(const void* pBuffer, int nBufferSize, bool bManageBuffer = false);
	virtual ~StreamReader();

	bool Read(void* pDataOut, int nSize);
	bool Skip(int nSize);

	void Reset();
	const void* GetBuffer();
	int GetSize();

private:
	bool m_bManageBuffer;
	const char* m_pBuffer;
	int m_nBufferSize;
	int m_nReadPos;

};

#endif // __STREAMREADER_H__
