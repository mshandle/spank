/*!
 * \file MsgNotifyLoginGift.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYLOGINGIFT_H__
#define __MSGNOTIFYLOGINGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyLoginGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2064,
		MSG_SIZE = 28,
	};

public:
	DECLARE_RTTI(MsgNotifyLoginGift, PokerMsgBase);

	MsgNotifyLoginGift();
	virtual ~MsgNotifyLoginGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nContinuousLogin;
	char nLastContinuousLogin;
	char _dummy[2];
	int64 _dummy1[2];

};

#endif // __MSGNOTIFYLOGINGIFT_H__
