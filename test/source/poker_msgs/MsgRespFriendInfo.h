/*!
 * \file MsgRespFriendInfo.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPFRIENDINFO_H__
#define __MSGRESPFRIENDINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespFriendInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2023,
		MSG_SIZE = 52,
	};

public:
	DECLARE_RTTI(MsgRespFriendInfo, PokerMsgBase);

	MsgRespFriendInfo();
	virtual ~MsgRespFriendInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nFriendUserId;
	char nInFacebook;
	uchar nLevel;
	char _dummy[2];
	int64 nCoins;
	int64 nMostCoins;
	int nCash;
	uint nLogoutTime;
	int64 nWinThisWeek;

};

#endif // __MSGRESPFRIENDINFO_H__
