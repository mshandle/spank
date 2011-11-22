/*!
 * \file MsgNotifyMttRank.h
 * \date unknown
 * 
 * 通知shootout等级
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYMTTRANK_H__
#define __MSGNOTIFYMTTRANK_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyMttRank : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2173,
		MSG_SIZE = 15,
	};

public:
	DECLARE_RTTI(MsgNotifyMttRank, PokerMsgBase);

	MsgNotifyMttRank();
	virtual ~MsgNotifyMttRank();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char nRank[3];	// Rank 为 -1时, 标识当前等级不可用~
	int nBonus[3];	// Bonus 为 -1时, 标识当前不可用~

};

#endif // __MSGNOTIFYMTTRANK_H__
