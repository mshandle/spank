/*!
 * \file MsgSeatUpdate.h
 * \date unknown
 * 
 * 更新单个座位的信息
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
	char nSeatId;	// 座位号
	char _dummy[3];
	NET_SEAT_INFO stSeatInfo;	// 座位信息

};

#endif // __MSGSEATUPDATE_H__
