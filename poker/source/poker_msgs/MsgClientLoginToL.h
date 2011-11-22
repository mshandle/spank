/*!
 * \file MsgClientLoginToL.h
 * \date unknown
 * 
 * 登入LoginServer
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGCLIENTLOGINTOL_H__
#define __MSGCLIENTLOGINTOL_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgClientLoginToL : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1002,
		MSG_SIZE = 400,
	};

public:
	DECLARE_RTTI(MsgClientLoginToL, PokerMsgBase);

	MsgClientLoginToL();
	virtual ~MsgClientLoginToL();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nSeqId;	// 序列号 目前无用 只是预留
	int64 nUserId;
	char szSessionKey[128];
	char szLoginSessionKey[128];
	char szLoginPassWord[128];
	uint nGroupId;	// 登录的服务器组ID(服务器的类型 如 英文版 土耳其版 类型为)

};

#endif // __MSGCLIENTLOGINTOL_H__
