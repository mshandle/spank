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
	int64 nRequestId;	// REQUEST的ID
	int64 nUserId;	// 发送REQUEST的玩家ID
	int64 nFriendId;	// 接收REQUEST的好友ID
	uint nRequestType;	// REQUEST类型
	int nPlatformId;	// 玩家登陆的平台id, 1表示facebook, 2表示google, 3表示igg, 4表示msn, 5表示twitter, 6表示yahoo
	char szNickName[32];	// 玩家昵称
	char szPlatAccount[255];	// 玩家登陆的平台账号

};

#endif // __MSGADDREQUEST_H__
