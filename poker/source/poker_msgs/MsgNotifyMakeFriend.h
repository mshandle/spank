/*!
 * \file MsgNotifyMakeFriend.h
 * \date unknown
 * 
 * 提示桌面上某座位的玩家请求加某座位的玩家为好友
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYMAKEFRIEND_H__
#define __MSGNOTIFYMAKEFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyMakeFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2019,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyMakeFriend, PokerMsgBase);

	MsgNotifyMakeFriend();
	virtual ~MsgNotifyMakeFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nSourceSeatId;	// 发起加好友请求的玩家座位ID
	char nDestSeatId;	// 收到好友请求的玩家座位ID
	char _dummy[2];

};

#endif // __MSGNOTIFYMAKEFRIEND_H__
