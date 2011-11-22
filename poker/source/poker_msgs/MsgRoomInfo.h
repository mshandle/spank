/*!
 * \file MsgRoomInfo.h
 * \date unknown
 * 
 * 进入房间后的回复
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGROOMINFO_H__
#define __MSGROOMINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRoomInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2006,
		MSG_SIZE = 420,
	};

public:
	DECLARE_RTTI(MsgRoomInfo, PokerMsgBase);

	MsgRoomInfo();
	virtual ~MsgRoomInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 目标用户的Id
	NET_ROOM_INFO stRoomInfo;	// 房间信息
	NET_SEAT_INFO stSeats[9];	// 座位信息 0 为牌官左手边第一个
	char nBanker;	// 庄家座位, 若游戏未开始, 则为-1.
	char nSmallBlind;	// 小盲注座位, 若游戏未开始, 则为-1.
	char nBigBlind;	// 大盲注座位, 若游戏未开始, 则为-1.
	char nPublicCards[5];	// 五张公牌, 没有的位置为-1.
	int64 nPools[8];	// 8个奖池, 没有的地方为0.
	uchar nHandCards[2];	// 玩家当前的手牌, 若无手牌, 则为255。
	char _dummy[2];

};

#endif // __MSGROOMINFO_H__
