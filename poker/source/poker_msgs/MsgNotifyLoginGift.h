/*!
 * \file MsgNotifyLoginGift.h
 * \date unknown
 * 
 * 弹出登录奖励领取框
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYLOGINGIFT_H__
#define __MSGNOTIFYLOGINGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyLoginGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2064,
		MSG_SIZE = 28,
	};

public:
	DECLARE_RTTI(MsgNotifyLoginGift, PokerMsgBase);

	MsgNotifyLoginGift();
	virtual ~MsgNotifyLoginGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nContinuousLogin;	// 连续登录天数(7天为上限)
	char nLastContinuousLogin;	// 上次连续登录天数
	char _dummy[2];
	int64 _dummy1[2];	// 防客户端崩溃的占位符, 在客户做完修改后应该删去。

};

#endif // __MSGNOTIFYLOGINGIFT_H__
