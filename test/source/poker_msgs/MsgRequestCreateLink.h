/*!
 * \file MsgRequestCreateLink.h
 * \date unknown
 * 
 * client请求发布幸运筹码
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTCREATELINK_H__
#define __MSGREQUESTCREATELINK_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestCreateLink : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2119,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestCreateLink, PokerMsgBase);

	MsgRequestCreateLink();
	virtual ~MsgRequestCreateLink();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uint nType;	// 发送幸运筹码的类型 1 幸运筹码 2 新年宝箱

};

#endif // __MSGREQUESTCREATELINK_H__
