/*!
 * \file MsgLoginServerValidate.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGLOGINSERVERVALIDATE_H__
#define __MSGLOGINSERVERVALIDATE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgLoginServerValidate : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1004,
		MSG_SIZE = 60,
	};

public:
	DECLARE_RTTI(MsgLoginServerValidate, PokerMsgBase);

	MsgLoginServerValidate();
	virtual ~MsgLoginServerValidate();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char szIp[16];
	int nPort;
	char szCheckOutText[24];
	int64 nIggId;

};

#endif // __MSGLOGINSERVERVALIDATE_H__
