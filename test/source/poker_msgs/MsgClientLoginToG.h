/*!
 * \file MsgClientLoginToG.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGCLIENTLOGINTOG_H__
#define __MSGCLIENTLOGINTOG_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgClientLoginToG : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1003,
		MSG_SIZE = 196,
	};

public:
	DECLARE_RTTI(MsgClientLoginToG, PokerMsgBase);

	MsgClientLoginToG();
	virtual ~MsgClientLoginToG();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nSeqId;
	int64 nUserId;
	char szCheckOutText[24];
	char szSessionKey[128];
	char szSignInLocale[32];

};

#endif // __MSGCLIENTLOGINTOG_H__
