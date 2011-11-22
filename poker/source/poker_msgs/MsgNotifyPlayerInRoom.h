/*!
 * \file MsgNotifyPlayerInRoom.h
 * \date unknown
 * 
 * 通知玩家离开房间
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
	int nRoomId;	// 表示SourceUserId所在的房间ID -1: 表示离开房间

};

#endif // __MSGNOTIFYPLAYERINROOM_H__
