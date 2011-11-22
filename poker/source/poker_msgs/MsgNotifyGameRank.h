/*!
 * \file MsgNotifyGameRank.h
 * \date unknown
 * 
 * 通知玩家在赛制房间内的比赛名次
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYGAMERANK_H__
#define __MSGNOTIFYGAMERANK_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyGameRank : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2074,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgNotifyGameRank, PokerMsgBase);

	MsgNotifyGameRank();
	virtual ~MsgNotifyGameRank();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nRank;
	char nBonusType;	// 奖金的类型: 1: 筹码 2: 金币
	char nGameType;	// 比赛的类型: 1: SNG 2: MTT
	char _dummy;
	int64 nBonus;

};

#endif // __MSGNOTIFYGAMERANK_H__
