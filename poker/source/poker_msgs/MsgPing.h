/*!
 * \file MsgPing.h
 * \date unknown
 * 
 * Ping包
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
	int nId;	// id, 由客户端自己定义, 可填0, 将原样返回
	int nTimestamp;	// 时间戳由客户端提供, 将原样返回

};

#endif // __MSGPING_H__
