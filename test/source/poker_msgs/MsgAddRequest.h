/*!
 * \file MsgAddRequest.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGADDREQUEST_H__
#define __MSGADDREQUEST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgAddRequest : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2148,
		MSG_SIZE = 319,
	};

public:
	DECLARE_RTTI(MsgAddRequest, PokerMsgBase);

	MsgAddRequest();
	virtual ~MsgAddRequest();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nRequestId;
	int64 nUserId;
	int64 nFriendId;
	uint nRequestType;
	int nPlatformId;
	char szNickName[32];
	char szPlatAccount[255];

};

#endif // __MSGADDREQUEST_H__
