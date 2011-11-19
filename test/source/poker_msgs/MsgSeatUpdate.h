/*!
 * \file MsgSeatUpdate.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSEATUPDATE_H__
#define __MSGSEATUPDATE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgSeatUpdate : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2009,
		MSG_SIZE = 44,
	};

public:
	DECLARE_RTTI(MsgSeatUpdate, PokerMsgBase);

	MsgSeatUpdate();
	virtual ~MsgSeatUpdate();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSeatId;
	char _dummy[3];
	NET_SEAT_INFO stSeatInfo;

};

#endif // __MSGSEATUPDATE_H__
