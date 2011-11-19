/*!
 * \file MsgUserStatus.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUSERSTATUS_H__
#define __MSGUSERSTATUS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUserStatus : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2058,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgUserStatus, PokerMsgBase);

	MsgUserStatus();
	virtual ~MsgUserStatus();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nStatus;
	char nReason;
	char _dummy[2];
	int nRoomId;

};

#endif // __MSGUSERSTATUS_H__
