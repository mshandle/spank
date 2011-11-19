/*!
 * \file MsgNotifyPublicCards.h
 * \date unknown
 * 
 * 公牌显示
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYPUBLICCARDS_H__
#define __MSGNOTIFYPUBLICCARDS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyPublicCards : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2015,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgNotifyPublicCards, PokerMsgBase);

	MsgNotifyPublicCards();
	virtual ~MsgNotifyPublicCards();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nCount;	// 牌数, 第一次发牌为3张, 第二次4张, 第三次5张
	char nCards[5];	// 范围为0~51, 表示52张牌中的一张
	char _dummy[2];	// 补齐位

};

#endif // __MSGNOTIFYPUBLICCARDS_H__
