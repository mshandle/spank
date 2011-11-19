/*!
 * \file MsgNotifyGiveGift.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYGIVEGIFT_H__
#define __MSGNOTIFYGIVEGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyGiveGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2113,
		MSG_SIZE = 32,
	};

public:
	DECLARE_RTTI(MsgNotifyGiveGift, PokerMsgBase);

	MsgNotifyGiveGift();
	virtual ~MsgNotifyGiveGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nItemType;
	int64 nGiverId;
	int64 nTakerId;
	char nGiveSeatId;
	char nTakerSeatId;
	char _dummy[2];

};

#endif // __MSGNOTIFYGIVEGIFT_H__
