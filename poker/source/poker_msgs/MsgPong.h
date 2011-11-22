/*!
 * \file MsgPong.h
 * \date unknown
 * 
 * Pong包
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGPONG_H__
#define __MSGPONG_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgPong : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1077,
		MSG_SIZE = 8,
	};

public:
	DECLARE_RTTI(MsgPong, PokerMsgBase);

	MsgPong();
	virtual ~MsgPong();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nId;	// id, 由客户端自己定义, 原样返回
	int nTimestamp;	// 时间戳由客户端提供, 原样返回

};

#endif // __MSGPONG_H__
