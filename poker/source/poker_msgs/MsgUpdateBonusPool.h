/*!
 * \file MsgUpdateBonusPool.h
 * \date unknown
 * 
 * 奖池更新包
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUPDATEBONUSPOOL_H__
#define __MSGUPDATEBONUSPOOL_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUpdateBonusPool : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2013,
		MSG_SIZE = 72,
	};

public:
	DECLARE_RTTI(MsgUpdateBonusPool, PokerMsgBase);

	MsgUpdateBonusPool();
	virtual ~MsgUpdateBonusPool();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nPool[8];	// 最多8个奖池, 主奖池编号为 0

};

#endif // __MSGUPDATEBONUSPOOL_H__
