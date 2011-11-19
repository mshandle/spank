/*!
 * \file MsgNotifyFirstLogin.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYFIRSTLOGIN_H__
#define __MSGNOTIFYFIRSTLOGIN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyFirstLogin : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2090,
		MSG_SIZE = 0,
	};

public:
	DECLARE_RTTI(MsgNotifyFirstLogin, PokerMsgBase);

	MsgNotifyFirstLogin();
	virtual ~MsgNotifyFirstLogin();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:

};

#endif // __MSGNOTIFYFIRSTLOGIN_H__
