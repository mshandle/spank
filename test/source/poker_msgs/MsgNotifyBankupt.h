/*!
 * \file MsgNotifyBankupt.h
 * \date unknown
 * 
 * 通知玩家破产相关消息
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
	int64 nProtectiveMoney;	// 本次保护金, 小于等于0则代表不再有保护金, 客户端需要自己定义这种情况下的行为
	int nTime;	// 第几次破产

};

#endif // __MSGNOTIFYBANKUPT_H__
