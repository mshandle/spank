/*!
 * \file MsgRequestJoinRoom.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTJOINROOM_H__
#define __MSGREQUESTJOINROOM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestJoinRoom : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2005,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestJoinRoom, PokerMsgBase);

	MsgRequestJoinRoom();
	virtual ~MsgRequestJoinRoom();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nRoomId;

};

#endif // __MSGREQUESTJOINROOM_H__
