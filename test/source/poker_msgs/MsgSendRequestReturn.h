/*!
 * \file MsgSendRequestReturn.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSENDREQUESTRETURN_H__
#define __MSGSENDREQUESTRETURN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgSendRequestReturn : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2145,
		MSG_SIZE = 319,
	};

public:
	DECLARE_RTTI(MsgSendRequestReturn, PokerMsgBase);

	MsgSendRequestReturn();
	virtual ~MsgSendRequestReturn();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nFriendUserId;
	int64 nRequestId;
	uint unRequestType;
	int nPlatformId;
	char szNickName[32];
	char szPlatformAccount[255];

};

#endif // __MSGSENDREQUESTRETURN_H__
