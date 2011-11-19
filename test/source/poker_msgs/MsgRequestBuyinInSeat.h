/*!
 * \file MsgRequestBuyinInSeat.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTBUYININSEAT_H__
#define __MSGREQUESTBUYININSEAT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestBuyinInSeat : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2034,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgRequestBuyinInSeat, PokerMsgBase);

	MsgRequestBuyinInSeat();
	virtual ~MsgRequestBuyinInSeat();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nBuyIn;

};

#endif // __MSGREQUESTBUYININSEAT_H__
