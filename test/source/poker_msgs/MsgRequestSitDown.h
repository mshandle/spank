/*!
 * \file MsgRequestSitDown.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTSITDOWN_H__
#define __MSGREQUESTSITDOWN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestSitDown : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2007,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgRequestSitDown, PokerMsgBase);

	MsgRequestSitDown();
	virtual ~MsgRequestSitDown();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSeatId;
	char _dummy[3];
	int64 nBuyIn;

};

#endif // __MSGREQUESTSITDOWN_H__
