/*!
 * \file MsgRespSitDown.h
 * \date unknown
 * 
 * 坐下请求的回复
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPSITDOWN_H__
#define __MSGRESPSITDOWN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespSitDown : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2008,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgRespSitDown, PokerMsgBase);

	MsgRespSitDown();
	virtual ~MsgRespSitDown();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nRoomId;	// 房间ID
	char nSeatId;	// 座位ID -1: 表示没有坐下
	char _dummy[3];
	int64 nCounter;	// 持有筹码

};

#endif // __MSGRESPSITDOWN_H__
