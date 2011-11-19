/*!
 * \file MsgNotifyMakeFriend.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYMAKEFRIEND_H__
#define __MSGNOTIFYMAKEFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyMakeFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2019,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyMakeFriend, PokerMsgBase);

	MsgNotifyMakeFriend();
	virtual ~MsgNotifyMakeFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSourceSeatId;
	char nDestSeatId;
	char _dummy[2];

};

#endif // __MSGNOTIFYMAKEFRIEND_H__
