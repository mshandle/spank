/*!
 * \file MsgNotifyHandCards.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYHANDCARDS_H__
#define __MSGNOTIFYHANDCARDS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyHandCards : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2014,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyHandCards, PokerMsgBase);

	MsgNotifyHandCards();
	virtual ~MsgNotifyHandCards();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSeatId;
	uchar nCards[2];
	char _dummy;

};

#endif // __MSGNOTIFYHANDCARDS_H__
