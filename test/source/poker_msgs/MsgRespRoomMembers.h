/*!
 * \file MsgRespRoomMembers.h
 * \date unknown
 * 
 * 房间内成员信息的回复
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPROOMMEMBERS_H__
#define __MSGRESPROOMMEMBERS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespRoomMembers : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2033,
		MSG_SIZE = 1216,
	};

public:
	DECLARE_RTTI(MsgRespRoomMembers, PokerMsgBase);

	MsgRespRoomMembers();
	virtual ~MsgRespRoomMembers();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	int nRoomId;	// 房间ID
	char nMemberType;	// 成员类型, 0: 所有成员, 1: 在座成员, 2: 旁观成员
	char nMemberNum;	// 此成员列表总人数
	char _dummy[2];
	NET_USER_INFO stMembers[30];	// 成员列表

};

#endif // __MSGRESPROOMMEMBERS_H__
