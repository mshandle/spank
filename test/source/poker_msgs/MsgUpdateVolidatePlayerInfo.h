/*!
 * \file MsgUpdateVolidatePlayerInfo.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUPDATEVOLIDATEPLAYERINFO_H__
#define __MSGUPDATEVOLIDATEPLAYERINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUpdateVolidatePlayerInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2068,
		MSG_SIZE = 40,
	};

public:
	DECLARE_RTTI(MsgUpdateVolidatePlayerInfo, PokerMsgBase);

	MsgUpdateVolidatePlayerInfo();
	virtual ~MsgUpdateVolidatePlayerInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nLevel;
	char _dummy[3];
	int64 nCoins;
	int64 nWinThisWeek;
	int nCash;
	uint nExp;
	int nTrinket;

};

#endif // __MSGUPDATEVOLIDATEPLAYERINFO_H__
