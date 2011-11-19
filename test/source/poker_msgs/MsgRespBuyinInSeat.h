/*!
 * \file MsgRespBuyinInSeat.h
 * \date unknown
 * 
 * 在座位上买筹码的回复
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPBUYININSEAT_H__
#define __MSGRESPBUYININSEAT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespBuyinInSeat : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2035,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRespBuyinInSeat, PokerMsgBase);

	MsgRespBuyinInSeat();
	virtual ~MsgRespBuyinInSeat();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nStatus;	// 执行的状态, 0: 成功, 1: 资金不足, 2: 超过最大买入值, 3: 小于最小买入
	char _dummy[3];	// 补齐位.

};

#endif // __MSGRESPBUYININSEAT_H__
