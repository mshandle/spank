/*!
 * \file MsgNotifyPlayerLevelUp.h
 * \date unknown
 * 
 * 通知玩家升级
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYPLAYERLEVELUP_H__
#define __MSGNOTIFYPLAYERLEVELUP_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyPlayerLevelUp : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2076,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyPlayerLevelUp, PokerMsgBase);

	MsgNotifyPlayerLevelUp();
	virtual ~MsgNotifyPlayerLevelUp();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nLevel;
	uchar nExp;
	char nSeatId;	// -1: 表示本人 0-8: 表示其他的座位
	char _dummy;

};

#endif // __MSGNOTIFYPLAYERLEVELUP_H__
