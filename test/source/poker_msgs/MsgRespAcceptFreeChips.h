/*!
 * \file MsgRespAcceptFreeChips.h
 * \date unknown
 * 
 * 接受好友的免费筹码的回复
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPACCEPTFREECHIPS_H__
#define __MSGRESPACCEPTFREECHIPS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespAcceptFreeChips : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2049,
		MSG_SIZE = 26,
	};

public:
	DECLARE_RTTI(MsgRespAcceptFreeChips, PokerMsgBase);

	MsgRespAcceptFreeChips();
	virtual ~MsgRespAcceptFreeChips();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char nResult;	// 操作结果。0: 成功, 1: 免费筹码不存在, 客户端可理解为此ID已经过期, 2: 已达到本日接收上限, 请明天再试
	char _dummy;	// 补齐
	int64 nUserId;	// 玩家的ID
	int64 nRequsetId;	// 请求的ID
	int64 nGeneratedChips;	// 生成的筹码数

};

#endif // __MSGRESPACCEPTFREECHIPS_H__
