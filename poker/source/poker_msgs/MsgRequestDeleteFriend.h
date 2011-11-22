/*!
 * \file MsgRequestDeleteFriend.h
 * \date unknown
 * 
 * Íæ¼ÒÇëÇóÉ¾³ýºÃÓÑ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTDELETEFRIEND_H__
#define __MSGREQUESTDELETEFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestDeleteFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2029,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgRequestDeleteFriend, PokerMsgBase);

	MsgRequestDeleteFriend();
	virtual ~MsgRequestDeleteFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nFriendUserId;

};

#endif // __MSGREQUESTDELETEFRIEND_H__
