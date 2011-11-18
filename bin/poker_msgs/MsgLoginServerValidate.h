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

class MsgLoginServerValidate : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1004,
		MSG_SIZE = 52,
	};

public:
	DECLARE_RTTI(MsgLoginServerValidate, PokerMsgBase);

	MsgLoginServerValidate();
	virtual ~MsgLoginServerValidate();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 userId;
	char ip[16];
	int port;
	char checkoutText[24];

};

#endif // __MSGLOGINSERVERVALIDATE_H__
