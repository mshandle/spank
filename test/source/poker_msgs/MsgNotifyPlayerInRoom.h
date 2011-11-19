/*!
 * \file MsgNotifyPlayerInRoom.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYPLAYERINROOM_H__
#define __MSGNOTIFYPLAYERINROOM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyPlayerInRoom : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2095,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgNotifyPlayerInRoom, PokerMsgBase);

	MsgNotifyPlayerInRoom();
	virtual ~MsgNotifyPlayerInRoom();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nSourceUserId;
	int nRoomId;

};

#endif // __MSGNOTIFYPLAYERINROOM_H__
