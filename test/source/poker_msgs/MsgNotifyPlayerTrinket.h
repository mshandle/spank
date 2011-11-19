/*!
 * \file MsgNotifyPlayerTrinket.h
 * \date unknown
 * 
 * 通知房间内其他玩家 某位玩家饰品发生变化
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYPLAYERTRINKET_H__
#define __MSGNOTIFYPLAYERTRINKET_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyPlayerTrinket : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2112,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgNotifyPlayerTrinket, PokerMsgBase);

	MsgNotifyPlayerTrinket();
	virtual ~MsgNotifyPlayerTrinket();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nTrinket;
	int64 nSourceUserId;
	char nSeatId;	// -2: 表示在大厅发送该消息包 0-8: Room发送该消息包 -1: 表示未坐下
	char _dummy[3];

};

#endif // __MSGNOTIFYPLAYERTRINKET_H__
