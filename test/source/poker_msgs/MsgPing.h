/*!
 * \file MsgPing.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGPING_H__
#define __MSGPING_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgPing : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1076,
		MSG_SIZE = 8,
	};

public:
	DECLARE_RTTI(MsgPing, PokerMsgBase);

	MsgPing();
	virtual ~MsgPing();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nId;
	int nTimestamp;

};

#endif // __MSGPING_H__
