/*!
 * \file MsgUserLoginOtherPlace.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUSERLOGINOTHERPLACE_H__
#define __MSGUSERLOGINOTHERPLACE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUserLoginOtherPlace : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2081,
		MSG_SIZE = 0,
	};

public:
	DECLARE_RTTI(MsgUserLoginOtherPlace, PokerMsgBase);

	MsgUserLoginOtherPlace();
	virtual ~MsgUserLoginOtherPlace();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:

};

#endif // __MSGUSERLOGINOTHERPLACE_H__
