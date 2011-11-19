/*!
 * \file MsgNotifyBankupt.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYBANKUPT_H__
#define __MSGNOTIFYBANKUPT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyBankupt : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2098,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyBankupt, PokerMsgBase);

	MsgNotifyBankupt();
	virtual ~MsgNotifyBankupt();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nProtectiveMoney;
	int nTime;

};

#endif // __MSGNOTIFYBANKUPT_H__
