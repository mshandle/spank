/*!
 * \file MsgUpdateVolidatePlayerInfo.h
 * \date unknown
 * 
 * 更新常变的玩家信息
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUPDATEVOLIDATEPLAYERINFO_H__
#define __MSGUPDATEVOLIDATEPLAYERINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUpdateVolidatePlayerInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2068,
		MSG_SIZE = 40,
	};

public:
	DECLARE_RTTI(MsgUpdateVolidatePlayerInfo, PokerMsgBase);

	MsgUpdateVolidatePlayerInfo();
	virtual ~MsgUpdateVolidatePlayerInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	uchar nLevel;	// 等级
	char _dummy[3];
	int64 nCoins;	// 总资产
	int64 nWinThisWeek;	// 本周赢额
	int nCash;	// 充值
	uint nExp;	// 经验值
	int nTrinket;	// 饰品

};

#endif // __MSGUPDATEVOLIDATEPLAYERINFO_H__
