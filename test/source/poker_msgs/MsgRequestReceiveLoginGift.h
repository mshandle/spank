/*!
 * \file MsgRequestReceiveLoginGift.h
 * \date unknown
 * 
 * 请求领取每日登录奖励
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTRECEIVELOGINGIFT_H__
#define __MSGREQUESTRECEIVELOGINGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestReceiveLoginGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2107,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestReceiveLoginGift, PokerMsgBase);

	MsgRequestReceiveLoginGift();
	virtual ~MsgRequestReceiveLoginGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nChoice;	// 玩家点击的, 范围为: 0~5
	char _dummy[3];	// 补齐位

};

#endif // __MSGREQUESTRECEIVELOGINGIFT_H__
