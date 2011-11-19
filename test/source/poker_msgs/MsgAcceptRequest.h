/*!
 * \file MsgAcceptRequest.h
 * \date unknown
 * 
 * 玩家点击赞助
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
	int64 nAcceptUserId;	// 点击accept赞助的玩家
	int64 nRequestUserId;	// 发送请求的玩家
	int64 nRequestId;	// 请求的ID
	uint nRequestType;	// 请求赞助的类型

};

#endif // __MSGACCEPTREQUEST_H__
