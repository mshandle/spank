/*!
 * \file MsgAcceptRequest.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGACCEPTREQUEST_H__
#define __MSGACCEPTREQUEST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgAcceptRequest : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2146,
		MSG_SIZE = 28,
	};

public:
	DECLARE_RTTI(MsgAcceptRequest, PokerMsgBase);

	MsgAcceptRequest();
	virtual ~MsgAcceptRequest();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nAcceptUserId;
	int64 nRequestUserId;
	int64 nRequestId;
	uint nRequestType;

};

#endif // __MSGACCEPTREQUEST_H__
