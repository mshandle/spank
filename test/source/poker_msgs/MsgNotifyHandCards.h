/*!
 * \file MsgNotifyHandCards.h
 * \date unknown
 * 
 * 手牌通知包
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYHANDCARDS_H__
#define __MSGNOTIFYHANDCARDS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyHandCards : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2014,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyHandCards, PokerMsgBase);

	MsgNotifyHandCards();
	virtual ~MsgNotifyHandCards();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSeatId;	// 座位号
	uchar nCards[2];	// 两张手牌, 范围为0~51, 表示52张牌中的一张
	char _dummy;	// 补齐位

};

#endif // __MSGNOTIFYHANDCARDS_H__
