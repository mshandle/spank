/*!
 * \file MsgRequestBuyItem.h
 * \date unknown
 * 
 * 
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
	int nItemType;
	char nBuyMethod;
	char nDestSeatId;
	char _dummy[2];
	int64 nCashCouponId;

};

#endif // __MSGREQUESTBUYITEM_H__
