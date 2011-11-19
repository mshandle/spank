/*!
 * \file MsgRespFriendStatus.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPFRIENDSTATUS_H__
#define __MSGRESPFRIENDSTATUS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespFriendStatus : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2025,
		MSG_SIZE = 1292,
	};

public:
	DECLARE_RTTI(MsgRespFriendStatus, PokerMsgBase);

	MsgRespFriendStatus();
	virtual ~MsgRespFriendStatus();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nCount;
	NET_FRIEND_STATUS stFriends[20];

};

#endif // __MSGRESPFRIENDSTATUS_H__
