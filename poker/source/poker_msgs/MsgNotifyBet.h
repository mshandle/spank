/*!
 * \file MsgNotifyBet.h
 * \date unknown
 * 
 * 通知下注
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYBET_H__
#define __MSGNOTIFYBET_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyBet : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2010,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyBet, PokerMsgBase);

	MsgNotifyBet();
	virtual ~MsgNotifyBet();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSeatId;	// 座位ID
	char nTime;	// 剩余等待时间, 单位为秒
	char nTotalTime;	// 总的等待时间, 用于播放倒计时动画
	char _dummy;	// 补齐位.

};

#endif // __MSGNOTIFYBET_H__
