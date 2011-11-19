/*!
 * \file MsgRequestFriendList.h
 * \date unknown
 * 
 * 玩家请求在线好友/牌友列表
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTFRIENDLIST_H__
#define __MSGREQUESTFRIENDLIST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestFriendList : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2022,
		MSG_SIZE = 8,
	};

public:
	DECLARE_RTTI(MsgRequestFriendList, PokerMsgBase);

	MsgRequestFriendList();
	virtual ~MsgRequestFriendList();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID

};

#endif // __MSGREQUESTFRIENDLIST_H__
