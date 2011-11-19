/*!
 * \file MsgNotice.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTICE_H__
#define __MSGNOTICE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotice : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2063,
		MSG_SIZE = 32,
	};

public:
	DECLARE_RTTI(MsgNotice, PokerMsgBase);

	MsgNotice();
	virtual ~MsgNotice();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nType;
	int64 nArg1;
	int64 nArg2;
	uint nTimestamp;

};

#endif // __MSGNOTICE_H__
