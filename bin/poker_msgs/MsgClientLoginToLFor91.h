/*!
 * \file MsgClientLoginToLFor91.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGCLIENTLOGINTOLFOR91_H__
#define __MSGCLIENTLOGINTOLFOR91_H__

#include "PokerMsgBase.h"

class MsgClientLoginToLFor91 : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2600,
		MSG_SIZE = 180,
	};

public:
	DECLARE_RTTI(MsgClientLoginToLFor91, PokerMsgBase);

	MsgClientLoginToLFor91();
	virtual ~MsgClientLoginToLFor91();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char uid[52];
	char sessionId[128];

};

#endif // __MSGCLIENTLOGINTOLFOR91_H__
