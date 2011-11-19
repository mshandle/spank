/*!
 * \file MsgNotifyGameState.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYGAMESTATE_H__
#define __MSGNOTIFYGAMESTATE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyGameState : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2012,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgNotifyGameState, PokerMsgBase);

	MsgNotifyGameState();
	virtual ~MsgNotifyGameState();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nBankerSeat;
	char nSmallBlindSeat;
	char nBigBlindSeat;
	char nGameStatus;
	char nRoomStatus;
	uchar nHandCards[2];
	char _dummy;

};

#endif // __MSGNOTIFYGAMESTATE_H__
