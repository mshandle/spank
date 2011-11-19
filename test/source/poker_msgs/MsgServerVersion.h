/*!
 * \file MsgServerVersion.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSERVERVERSION_H__
#define __MSGSERVERVERSION_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgServerVersion : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2086,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgServerVersion, PokerMsgBase);

	MsgServerVersion();
	virtual ~MsgServerVersion();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	uint nVersionId;
	ushort nYear;
	uchar nMonth;
	uchar nDay;
	uchar nHour;
	uchar nMinute;
	uchar nSecond;
	uchar _dummy;

};

#endif // __MSGSERVERVERSION_H__
