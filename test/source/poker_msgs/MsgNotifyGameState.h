/*!
 * \file MsgNotifyGameState.h
 * \date unknown
 * 
 * 游戏开局通知包
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYGAMESTATE_H__
#define __MSGNOTIFYGAMESTATE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyGameState : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2012,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgNotifyGameState, PokerMsgBase);

	MsgNotifyGameState();
	virtual ~MsgNotifyGameState();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nBankerSeat;	// 庄家座位ID
	char nSmallBlindSeat;	// 小盲注座位ID
	char nBigBlindSeat;	// 大盲注座位ID
	char nGameStatus;	// 游戏状态, 0: 未开局, 1: 已开局.
	char nRoomStatus;	// 房间状态: 0: stopping 1: running 
	uchar nHandCards[2];	// 玩家当前的手牌, 范围为0~51, 表示52张牌中的一张, 若无手牌, 则为255.
	char _dummy;

};

#endif // __MSGNOTIFYGAMESTATE_H__
