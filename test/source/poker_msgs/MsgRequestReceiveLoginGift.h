/*!
 * \file MsgRequestReceiveLoginGift.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTRECEIVELOGINGIFT_H__
#define __MSGREQUESTRECEIVELOGINGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestReceiveLoginGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2107,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestReceiveLoginGift, PokerMsgBase);

	MsgRequestReceiveLoginGift();
	virtual ~MsgRequestReceiveLoginGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nChoice;
	char _dummy[3];

};

#endif // __MSGREQUESTRECEIVELOGINGIFT_H__
