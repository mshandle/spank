/*!
 * \file MsgNotifyIsSendLuckyChips.h
 * \date unknown
 * 
 * 通知client是否发布过幸运筹码
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYISSENDLUCKYCHIPS_H__
#define __MSGNOTIFYISSENDLUCKYCHIPS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyIsSendLuckyChips : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2118,
		MSG_SIZE = 4,
	};

public:
	DECLARE_RTTI(MsgNotifyIsSendLuckyChips, PokerMsgBase);

	MsgNotifyIsSendLuckyChips();
	virtual ~MsgNotifyIsSendLuckyChips();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nIsSendLuckyChips;

};

#endif // __MSGNOTIFYISSENDLUCKYCHIPS_H__
