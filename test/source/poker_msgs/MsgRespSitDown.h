/*!
 * \file MsgRespSitDown.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPSITDOWN_H__
#define __MSGRESPSITDOWN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespSitDown : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2008,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgRespSitDown, PokerMsgBase);

	MsgRespSitDown();
	virtual ~MsgRespSitDown();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nRoomId;
	char nSeatId;
	char _dummy[3];
	int64 nCounter;

};

#endif // __MSGRESPSITDOWN_H__
