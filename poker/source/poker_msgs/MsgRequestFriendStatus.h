/*!
 * \file MsgRequestFriendStatus.h
 * \date unknown
 * 
 * 在线玩家请求好友/牌友状态
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTFRIENDSTATUS_H__
#define __MSGREQUESTFRIENDSTATUS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestFriendStatus : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2024,
		MSG_SIZE = 8,
	};

public:
	DECLARE_RTTI(MsgRequestFriendStatus, PokerMsgBase);

	MsgRequestFriendStatus();
	virtual ~MsgRequestFriendStatus();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID

};

#endif // __MSGREQUESTFRIENDSTATUS_H__
