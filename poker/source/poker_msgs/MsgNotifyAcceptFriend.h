/*!
 * \file MsgNotifyAcceptFriend.h
 * \date unknown
 * 
 * 提示桌面上某两座位的玩家已成为好友
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYACCEPTFRIEND_H__
#define __MSGNOTIFYACCEPTFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyAcceptFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2021,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyAcceptFriend, PokerMsgBase);

	MsgNotifyAcceptFriend();
	virtual ~MsgNotifyAcceptFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nSourceSeatId;	// 发起加好友请求的玩家座位ID
	char nDestSeatId;	// 收到好友请求的玩家座位ID
	char _dummy[2];

};

#endif // __MSGNOTIFYACCEPTFRIEND_H__
