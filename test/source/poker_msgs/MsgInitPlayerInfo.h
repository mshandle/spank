/*!
 * \file MsgInitPlayerInfo.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGINITPLAYERINFO_H__
#define __MSGINITPLAYERINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgInitPlayerInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2067,
		MSG_SIZE = 70,
	};

public:
	DECLARE_RTTI(MsgInitPlayerInfo, PokerMsgBase);

	MsgInitPlayerInfo();
	virtual ~MsgInitPlayerInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nLevel;
	uchar nFlags;
	uchar nShootOutRank;
	char nShootOutPlace[3];
	int64 nCoins;
	int64 nMostCoins;
	int64 nWinThisWeek;
	int nCash;
	uint nExp;
	int64 nChampionInBuddiesLastWeek;
	int64 nMostWinInBuddiesLastWeek;
	int nTrinket;
	uint nTutorialFlags;

};

#endif // __MSGINITPLAYERINFO_H__
