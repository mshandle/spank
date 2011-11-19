/*!
 * \file MsgRequestRoomMembers.h
 * \date unknown
 * 
 * 
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
	int64 nUserId;
	int nRoomId;
	char nMemberType;
	char _dummy[3];

};

#endif // __MSGREQUESTROOMMEMBERS_H__
