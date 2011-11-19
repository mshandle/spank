/*!
 * \file MsgNotifyEmotion.h
 * \date unknown
 * 
 * 服务器广播表情
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYEMOTION_H__
#define __MSGNOTIFYEMOTION_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyEmotion : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2051,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyEmotion, PokerMsgBase);

	MsgNotifyEmotion();
	virtual ~MsgNotifyEmotion();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nSeat;	// 座位ID
	short nEmot;	// 表情ID, 实际表情由客户端指定
	char _dummy;	// 对齐位

};

#endif // __MSGNOTIFYEMOTION_H__
