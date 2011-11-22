/*!
 * \file MsgAccountForceOut.h
 * \date unknown
 * 
 * 通知客户端帐号被封存
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGACCOUNTFORCEOUT_H__
#define __MSGACCOUNTFORCEOUT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgAccountForceOut : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2121,
		MSG_SIZE = 0,
	};

public:
	DECLARE_RTTI(MsgAccountForceOut, PokerMsgBase);

	MsgAccountForceOut();
	virtual ~MsgAccountForceOut();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:

};

#endif // __MSGACCOUNTFORCEOUT_H__
