/*!
 * \file PokerMsgBase.h
 * \date 11-17-2011 16:14:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __POKERMSGBASE_H__
#define __POKERMSGBASE_H__

#include <net/INetMsgBase.h>

class PokerMsgBase : public INetMsgBase
{
public:
	DECLARE_RTTI(PokerMsgBase, INetMsgBase);

	PokerMsgBase(short type, short size);
	virtual ~PokerMsgBase();

	short GetType() const;

	virtual bool FromStream(StreamReader* pReader);
	virtual bool ToStream(StreamWriter* pWriter);

	virtual bool Unpack(StreamReader* pReader) = 0;
	virtual bool Pack(StreamWriter* pWriter) = 0;

private:
	short m_Type;
	short m_Size;

};
#endif // __POKERMSGBASE_H__
