/*!
 * \file MsgRespBuyItem.h
 * \date unknown
 * 
 * 答复购买道具的请求
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPBUYITEM_H__
#define __MSGRESPBUYITEM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespBuyItem : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2082,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgRespBuyItem, PokerMsgBase);

	MsgRespBuyItem();
	virtual ~MsgRespBuyItem();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 购买者Id
	int nItemType;	// 购买到的物品类型 -1: 表示购买失败
	int64 nCashCouponId;	// 正在使用的代金券Id -1: 表示空
	int nCashCouponBalance;	// 正在使用的代金券余额 -1: 表示空

};

#endif // __MSGRESPBUYITEM_H__
