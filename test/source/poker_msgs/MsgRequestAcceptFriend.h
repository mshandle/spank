/*!
 * \file MsgRequestAcceptFriend.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTACCEPTFRIEND_H__
#define __MSGREQUESTACCEPTFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestAcceptFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2020,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestAcceptFriend, PokerMsgBase);

	MsgRequestAcceptFriend();
	virtual ~MsgRequestAcceptFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSourceSeatId;
	char _dummy[3];

};

#endif // __MSGREQUESTACCEPTFRIEND_H__
