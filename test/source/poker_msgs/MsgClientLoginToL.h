/*!
 * \file MsgClientLoginToL.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGCLIENTLOGINTOL_H__
#define __MSGCLIENTLOGINTOL_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgClientLoginToL : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1002,
		MSG_SIZE = 400,
	};

public:
	DECLARE_RTTI(MsgClientLoginToL, PokerMsgBase);

	MsgClientLoginToL();
	virtual ~MsgClientLoginToL();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nSeqId;
	int64 nUserId;
	char szSessionKey[128];
	char szLoginSessionKey[128];
	char szLoginPassWord[128];
	uint nGroupId;

};

#endif // __MSGCLIENTLOGINTOL_H__
