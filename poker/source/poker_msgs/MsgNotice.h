/*!
 * \file MsgNotice.h
 * \date unknown
 * 
 * 通知消息包
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
	int nType;	// 通知消息类型, 用于决定使用的通知模板。1: 每日登录获得 $Arg1 奖励筹码; 2: 从周锦标赛获得 $Arg1 奖金。3: 从新手教程获得 $Arg1 筹码 和 $Arg2 经验值 4: 通过链接领取奖励 $Arg1 筹码数 $Arg2 链接类型(0为系统发布的链接 1为幸运筹码的链接 2为新年宝箱share的链接]
	int64 nArg1;	// 通知参数1
	int64 nArg2;	// 通知参数2
	uint nTimestamp;	// 时间戳

};

#endif // __MSGNOTICE_H__
