/*!
 * \file MsgSendRoleRequestList.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSENDROLEREQUESTLIST_H__
#define __MSGSENDROLEREQUESTLIST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgSendRoleRequestList : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2143,
		MSG_SIZE = 330,
	};

public:
	DECLARE_RTTI(MsgSendRoleRequestList, PokerMsgBase);

	MsgSendRoleRequestList();
	virtual ~MsgSendRoleRequestList();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 UserId;
	bool bTail;
	char _dummy;
	NET_REQUEST_DATA stRequestList[10];

};

#endif // __MSGSENDROLEREQUESTLIST_H__
