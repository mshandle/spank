/*!
 * \file MsgRespFriendInfo.h
 * \date unknown
 * 
 * 在线好友/牌友信息，每次一个，可发多个
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPFRIENDINFO_H__
#define __MSGRESPFRIENDINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespFriendInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2023,
		MSG_SIZE = 52,
	};

public:
	DECLARE_RTTI(MsgRespFriendInfo, PokerMsgBase);

	MsgRespFriendInfo();
	virtual ~MsgRespFriendInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	int64 nFriendUserId;	// 好友ID
	char nInFacebook;	// 是否 Facebook 好友
	uchar nLevel;	// 等级
	char _dummy[2];	// 补齐位
	int64 nCoins;	// 总资产
	int64 nMostCoins;	// 总资产的历史最高记录
	int nCash;	// 充值
	uint nLogoutTime;
	int64 nWinThisWeek;	// 本周赢额

};

#endif // __MSGRESPFRIENDINFO_H__
