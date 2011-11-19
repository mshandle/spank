/*!
 * \file MsgRespBuyinInSeat.h
 * \date unknown
 * 
 * 
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
	int64 nUserId;
	char nStatus;
	char _dummy[3];

};

#endif // __MSGRESPBUYININSEAT_H__
