/*!
 * \file MsgRespRoomMembers.h
 * \date unknown
 * 
 * 
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
	int64 nUserId;
	int nRoomId;
	char nMemberType;
	char nMemberNum;
	char _dummy[2];
	NET_USER_INFO stMembers[30];

};

#endif // __MSGRESPROOMMEMBERS_H__
