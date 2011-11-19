/*!
 * \file MsgNotifyRoomMessage.h
 * \date unknown
 * 
 * 通知房间内的聊天信息
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYROOMMESSAGE_H__
#define __MSGNOTIFYROOMMESSAGE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyRoomMessage : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2028,
		MSG_SIZE = 29,
	};

public:
	DECLARE_RTTI(MsgNotifyRoomMessage, PokerMsgBase);

	MsgNotifyRoomMessage();
	virtual ~MsgNotifyRoomMessage();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	int64 nSenderUserId;	// 发起聊天消息的玩家ID
	short nMsgLength;	// 聊天信息长度.
	char _dummy[2];
	int64 nDest;	// 目标玩家, 须是同房间内的玩家。-1: 房间内群发
	char nMessage;	// 聊天信息内容

};

#endif // __MSGNOTIFYROOMMESSAGE_H__
