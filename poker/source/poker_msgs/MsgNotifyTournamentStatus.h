/*!
 * \file MsgNotifyTournamentStatus.h
 * \date unknown
 * 
 * 通知客户端房间状态
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYTOURNAMENTSTATUS_H__
#define __MSGNOTIFYTOURNAMENTSTATUS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyTournamentStatus : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2102,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyTournamentStatus, PokerMsgBase);

	MsgNotifyTournamentStatus();
	virtual ~MsgNotifyTournamentStatus();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nRoomStatus;	// 1.running  0.stopping
	char _dummy[3];

};

#endif // __MSGNOTIFYTOURNAMENTSTATUS_H__
