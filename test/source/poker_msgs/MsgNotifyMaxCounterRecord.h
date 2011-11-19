/*!
 * \file MsgNotifyMaxCounterRecord.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYMAXCOUNTERRECORD_H__
#define __MSGNOTIFYMAXCOUNTERRECORD_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyMaxCounterRecord : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2103,
		MSG_SIZE = 52,
	};

public:
	DECLARE_RTTI(MsgNotifyMaxCounterRecord, PokerMsgBase);

	MsgNotifyMaxCounterRecord();
	virtual ~MsgNotifyMaxCounterRecord();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nOldRecordUserId;
	int64 nOldRecordCounter;
	int64 nNewRecordUserId;
	int64 nNewRecordCounter;
	int64 nSmallBlind;
	int nCount;

};

#endif // __MSGNOTIFYMAXCOUNTERRECORD_H__
