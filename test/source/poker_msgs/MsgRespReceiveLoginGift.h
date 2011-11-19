/*!
 * \file MsgRespReceiveLoginGift.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPRECEIVELOGINGIFT_H__
#define __MSGRESPRECEIVELOGINGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespReceiveLoginGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2108,
		MSG_SIZE = 68,
	};

public:
	DECLARE_RTTI(MsgRespReceiveLoginGift, PokerMsgBase);

	MsgRespReceiveLoginGift();
	virtual ~MsgRespReceiveLoginGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nResult;
	char nChoice;
	char _dummy[2];
	int64 nPots[6];
	int64 nBonus;

};

#endif // __MSGRESPRECEIVELOGINGIFT_H__
