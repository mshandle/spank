/*!
 * \file MsgNotifyPlayerTrinket.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYPLAYERTRINKET_H__
#define __MSGNOTIFYPLAYERTRINKET_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyPlayerTrinket : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2112,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgNotifyPlayerTrinket, PokerMsgBase);

	MsgNotifyPlayerTrinket();
	virtual ~MsgNotifyPlayerTrinket();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nTrinket;
	int64 nSourceUserId;
	char nSeatId;
	char _dummy[3];

};

#endif // __MSGNOTIFYPLAYERTRINKET_H__
