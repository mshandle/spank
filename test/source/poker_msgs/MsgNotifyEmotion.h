/*!
 * \file MsgNotifyEmotion.h
 * \date unknown
 * 
 * 
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
	int64 nUserId;
	char nSeat;
	short nEmot;
	char _dummy;

};

#endif // __MSGNOTIFYEMOTION_H__
