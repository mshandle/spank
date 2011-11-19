/*!
 * \file MsgRequestInviteFriend.h
 * \date unknown
 * 
 * 玩家邀请好友加入房间
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTINVITEFRIEND_H__
#define __MSGREQUESTINVITEFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestInviteFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2030,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgRequestInviteFriend, PokerMsgBase);

	MsgRequestInviteFriend();
	virtual ~MsgRequestInviteFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	int64 nFriendUserId;	// 被邀请的好友玩家ID
	int nRoomId;	// 玩家当前的RoomId

};

#endif // __MSGREQUESTINVITEFRIEND_H__
