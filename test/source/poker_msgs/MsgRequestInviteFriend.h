/*!
 * \file MsgRequestInviteFriend.h
 * \date unknown
 * 
 * 
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
	int64 nUserId;
	int64 nFriendUserId;
	int nRoomId;

};

#endif // __MSGREQUESTINVITEFRIEND_H__
