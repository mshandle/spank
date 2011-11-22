/*!
 * \file MsgSendRequestReturn.h
 * \date unknown
 * 
 * 玩家发送请求返回的结果
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
	int64 nUserId;	// 玩家ID
	int64 nFriendUserId;	// 好友的玩家ID
	int64 nRequestId;	// 数据库返回的该request的唯一ID
	uint unRequestType;	// 请求的类型
	int nPlatformId;	// 玩家登陆的平台id, 1表示facebook, 2表示google, 3表示igg, 4表示msn, 5表示twitter, 6表示yahoo
	char szNickName[32];	// 玩家昵称
	char szPlatformAccount[255];	// 玩家登陆的平台账号

};

#endif // __MSGSENDREQUESTRETURN_H__
