/*!
 * \file MsgRequestRoomMessage.h
 * \date unknown
 * 
 * 玩家房间内聊天请示
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTROOMMESSAGE_H__
#define __MSGREQUESTROOMMESSAGE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestRoomMessage : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2027,
		MSG_SIZE = 148,
	};

public:
	DECLARE_RTTI(MsgRequestRoomMessage, PokerMsgBase);

	MsgRequestRoomMessage();
	virtual ~MsgRequestRoomMessage();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 本玩家ID
	short nMsgLength;	// 聊天信息长度.
	char _dummy[2];
	int64 nDest;	// 目标玩家, 须是同房间内的玩家。-1: 房间内群发
	char szMessage[128];	// 聊天信息内容

};

#endif // __MSGREQUESTROOMMESSAGE_H__
