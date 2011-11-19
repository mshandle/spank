/*!
 * \file MsgRequestJoinRoom.h
 * \date unknown
 * 
 * 请求进入房间
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
	int nRoomId;	// -1: 表示离开房间 -10 快速进入 low -11 快速进入 mid -12 快速进入 high -20 进入MTT 等级1 -21 进入MTT等级2 -22 进入MTT等级3 -30 进入 周锦标赛 -510 快速进入5人房

};

#endif // __MSGREQUESTJOINROOM_H__
