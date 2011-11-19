/*!
 * \file MsgRequestRoomMembers.h
 * \date unknown
 * 
 * 请求房间内成员信息
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTROOMMEMBERS_H__
#define __MSGREQUESTROOMMEMBERS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestRoomMembers : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2032,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgRequestRoomMembers, PokerMsgBase);

	MsgRequestRoomMembers();
	virtual ~MsgRequestRoomMembers();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	int nRoomId;	// 房间ID
	char nMemberType;	// 成员类型, 0: 所有成员, 1: 在座成员, 2: 旁观成员
	char _dummy[3];	// 请求房间内成员信息。

};

#endif // __MSGREQUESTROOMMEMBERS_H__
