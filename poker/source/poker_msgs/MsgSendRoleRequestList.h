/*!
 * \file MsgSendRoleRequestList.h
 * \date unknown
 * 
 * 向玩家发送requests列表
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
	int64 UserId;	// 玩家的ID
	bool bTail;	// 是否结尾
	char _dummy;	// 占位符
	NET_REQUEST_DATA stRequestList[10];	// 玩家的REQUEST 列表

};

#endif // __MSGSENDROLEREQUESTLIST_H__
