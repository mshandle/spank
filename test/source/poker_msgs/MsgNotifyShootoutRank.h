/*!
 * \file MsgNotifyShootoutRank.h
 * \date unknown
 * 
 * 通知玩家目前MTT等级
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYSHOOTOUTRANK_H__
#define __MSGNOTIFYSHOOTOUTRANK_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyShootoutRank : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2056,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyShootoutRank, PokerMsgBase);

	MsgNotifyShootoutRank();
	virtual ~MsgNotifyShootoutRank();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// 玩家ID
	char nShootOutRank;	// 玩家目前达到ShootOut的等级
	char _dummp[3];

};

#endif // __MSGNOTIFYSHOOTOUTRANK_H__
