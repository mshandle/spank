/*!
 * \file MsgNotifyMaxCounterRecord.h
 * \date unknown
 * 
 * 通知客户端赢得筹码最新纪录
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
	int64 nOldRecordUserId;	// 旧纪录userId 如果为0表示这次纪录是第一次
	int64 nOldRecordCounter;	// 旧纪录筹码
	int64 nNewRecordUserId;	// 新纪录userId
	int64 nNewRecordCounter;	// 新纪录筹码
	int64 nSmallBlind;	// 0: 表示这次纪录是全服纪录 不为0: 表示该小盲注类型房间的纪录
	int nCount;	// 第几次破记录 全服记录不统计该项

};

#endif // __MSGNOTIFYMAXCOUNTERRECORD_H__
