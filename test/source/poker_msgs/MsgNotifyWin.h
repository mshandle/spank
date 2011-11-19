/*!
 * \file MsgNotifyWin.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYWIN_H__
#define __MSGNOTIFYWIN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyWin : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2016,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgNotifyWin, PokerMsgBase);

	MsgNotifyWin();
	virtual ~MsgNotifyWin();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nPoolId;
	short nSeatIds;
	char _dummy;
	int64 nBonus;

};

#endif // __MSGNOTIFYWIN_H__
