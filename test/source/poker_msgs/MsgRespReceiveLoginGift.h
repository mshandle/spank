/*!
 * \file MsgRespReceiveLoginGift.h
 * \date unknown
 * 
 * 领取每日登录奖励的结果
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPRECEIVELOGINGIFT_H__
#define __MSGRESPRECEIVELOGINGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespReceiveLoginGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2108,
		MSG_SIZE = 68,
	};

public:
	DECLARE_RTTI(MsgRespReceiveLoginGift, PokerMsgBase);

	MsgRespReceiveLoginGift();
	virtual ~MsgRespReceiveLoginGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nResult;	// 0: 表示成功领取, 1: 已领取过, -1: 内部错误
	char nChoice;	// 玩家点击的项, 范围为: 0~5
	char _dummy[2];
	int64 nPots[6];	// 六个可选项
	int64 nBonus;	// 实际获得的奖金

};

#endif // __MSGRESPRECEIVELOGINGIFT_H__
