/*!
 * \file MsgRequestBuyItem.h
 * \date unknown
 * 
 * 请求买入物品
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTBUYITEM_H__
#define __MSGREQUESTBUYITEM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestBuyItem : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2075,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgRequestBuyItem, PokerMsgBase);

	MsgRequestBuyItem();
	virtual ~MsgRequestBuyItem();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nItemType;	// 购买物品的类型
	char nBuyMethod;	// 购买方式, 1: 正常chip价格, 2: 特殊chip价格, 3: VIPchip价格, 4: 正常gold价格, 5: 特殊gold价格, 6: VIPgold价格 
	char nDestSeatId;	// 赠送的目标座位Id -2: 无赠送, -1: 送给全桌, 0-8: 目标座位Id
	char _dummy[2];
	int64 nCashCouponId;	// 如果使用代金券的话发送代金券的Id 否则为-1

};

#endif // __MSGREQUESTBUYITEM_H__
