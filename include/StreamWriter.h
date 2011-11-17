/*!
 * \file StreamWriter.h
 * \date 18-05-2011 22:55:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __STREAMWRITER_H__
#define __STREAMWRITER_H__

#include "IObject.h"

class StreamWriter : public IObject
{
public:
	enum CONST_DEFINE
	{
		BLOCK_ALIGN = 128,
	};

public:
	DECLARE_RTTI(StreamWriter, IObject);

	StreamWriter();
	virtual ~StreamWriter();

	bool Write(const void* pData, int nSize);

	void Reset();
	const void* GetBuffer();
	int GetBufferSize();

private:
	bool Expend(int nRequireSize);

private:
	char* m_pBuffer;
	int m_nSize;
	int m_nPos;

};
#endif // __STREAMWRITER_H__
