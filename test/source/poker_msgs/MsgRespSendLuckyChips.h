/*!
 * \file MsgRespSendLuckyChips.h
 * \date unknown
 * 
 * 
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
	uint nType;

};

#endif // __MSGRESPSENDLUCKYCHIPS_H__
