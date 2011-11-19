/*!
 * \file MsgRespFriendStatusEnd.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPFRIENDSTATUSEND_H__
#define __MSGRESPFRIENDSTATUSEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespFriendStatusEnd : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2026,
		MSG_SIZE = 8,
	};

public:
	DECLARE_RTTI(MsgRespFriendStatusEnd, PokerMsgBase);

	MsgRespFriendStatusEnd();
	virtual ~MsgRespFriendStatusEnd();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;

};

#endif // __MSGRESPFRIENDSTATUSEND_H__
