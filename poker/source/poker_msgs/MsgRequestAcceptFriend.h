/*!
 * \file MsgRequestAcceptFriend.h
 * \date unknown
 * 
 * 玩家接受好友的请求包
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTACCEPTFRIEND_H__
#define __MSGREQUESTACCEPTFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestAcceptFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2020,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestAcceptFriend, PokerMsgBase);

	MsgRequestAcceptFriend();
	virtual ~MsgRequestAcceptFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 本玩家ID
	char nSourceSeatId;	// 接受此座位的玩家的好友请求
	char _dummy[3];

};

#endif // __MSGREQUESTACCEPTFRIEND_H__
