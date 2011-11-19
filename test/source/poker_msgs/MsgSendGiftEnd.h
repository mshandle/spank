/*!
 * \file MsgSendGiftEnd.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSENDGIFTEND_H__
#define __MSGSENDGIFTEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgSendGiftEnd : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2114,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgSendGiftEnd, PokerMsgBase);

	MsgSendGiftEnd();
	virtual ~MsgSendGiftEnd();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nTakerId;
	int nItemType;

};

#endif // __MSGSENDGIFTEND_H__
