/*!
 * \file MsgRespSendLuckyChips.h
 * \date unknown
 * 
 * 回复幸运筹码发布结果
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPSENDLUCKYCHIPS_H__
#define __MSGRESPSENDLUCKYCHIPS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespSendLuckyChips : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2120,
		MSG_SIZE = 40,
	};

public:
	DECLARE_RTTI(MsgRespSendLuckyChips, PokerMsgBase);

	MsgRespSendLuckyChips();
	virtual ~MsgRespSendLuckyChips();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char nLinkId[36];
	uint nType;	// 返回的类型

};

#endif // __MSGRESPSENDLUCKYCHIPS_H__
