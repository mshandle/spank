/*!
 * \file MsgRespUseItem.h
 * \date unknown
 * 
 * 使用道具的回复
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPUSEITEM_H__
#define __MSGRESPUSEITEM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespUseItem : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2105,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgRespUseItem, PokerMsgBase);

	MsgRespUseItem();
	virtual ~MsgRespUseItem();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nItemId;	// 使用的物品ID
	char nIsSuccess;	// 1: 使用成功 0: 使用失败
	char _dummy[3];

};

#endif // __MSGRESPUSEITEM_H__
