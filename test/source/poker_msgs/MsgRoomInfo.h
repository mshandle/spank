/*!
 * \file MsgRoomInfo.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGROOMINFO_H__
#define __MSGROOMINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRoomInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2006,
		MSG_SIZE = 420,
	};

public:
	DECLARE_RTTI(MsgRoomInfo, PokerMsgBase);

	MsgRoomInfo();
	virtual ~MsgRoomInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	NET_ROOM_INFO stRoomInfo;
	NET_SEAT_INFO stSeats[9];
	char nBanker;
	char nSmallBlind;
	char nBigBlind;
	char nPublicCards[5];
	int64 nPools[8];
	uchar nHandCards[2];
	char _dummy[2];

};

#endif // __MSGROOMINFO_H__
