/*!
 * \file MsgNotifyWin.h
 * \date unknown
 * 
 * 公牌通知包
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYWIN_H__
#define __MSGNOTIFYWIN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyWin : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2016,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgNotifyWin, PokerMsgBase);

	MsgNotifyWin();
	virtual ~MsgNotifyWin();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nPoolId;	// 奖池Id, 如果为唯一未弃牌的人赢的情况, 此项为-1, 表示所有奖池一次性发放
	short nSeatIds;	// 获奖的所有座位Id, 以位表示. 第0位为1时, 指第0个座位获得了这个奖池。可以指定多个.
	char _dummy;
	int64 nBonus;	// 奖金, 每个人从这个奖池所获得的奖金。

};

#endif // __MSGNOTIFYWIN_H__
