/*!
 * \file MsgInitPlayerInfo.h
 * \date unknown
 * 
 * 登录时初始化的玩家信息
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGINITPLAYERINFO_H__
#define __MSGINITPLAYERINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgInitPlayerInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2067,
		MSG_SIZE = 70,
	};

public:
	DECLARE_RTTI(MsgInitPlayerInfo, PokerMsgBase);

	MsgInitPlayerInfo();
	virtual ~MsgInitPlayerInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	uchar nLevel;	// 等级
	uchar nFlags;	// 标志位。0位: 是否粉丝, (1位: 是否加了书签, 2位: 是否允许发邮件, 3位: 是否允许发NewsFeed), 4位: 是否VIP, 5位: 是否GM 注, 目前1, 2, 3, 4位已经失效。
	uchar nShootOutRank;	// MTT目前等级
	char nShootOutPlace[3];	// MTT历史名次信息
	int64 nCoins;	// 总资产
	int64 nMostCoins;	// 总资产的历史最高记录
	int64 nWinThisWeek;	// 本周赢额
	int nCash;	// 充值
	uint nExp;	// 经验值
	int64 nChampionInBuddiesLastWeek;	// 上周大赢家的玩家ID
	int64 nMostWinInBuddiesLastWeek;	// 上周大赢家的赢额
	int nTrinket;
	uint nTutorialFlags;	// 新手教程完成度标志位

};

#endif // __MSGINITPLAYERINFO_H__
