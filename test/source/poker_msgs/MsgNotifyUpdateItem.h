/*!
 * \file MsgNotifyUpdateItem.h
 * \date unknown
 * 
 * 通知client道具列表中获得新道具或删除道具
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYUPDATEITEM_H__
#define __MSGNOTIFYUPDATEITEM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyUpdateItem : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2099,
		MSG_SIZE = 48,
	};

public:
	DECLARE_RTTI(MsgNotifyUpdateItem, PokerMsgBase);

	MsgNotifyUpdateItem();
	virtual ~MsgNotifyUpdateItem();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nType;	// 1: 添加 0: 删除 2: 更新
	char _dummy[3];
	NET_ITEM_INFO nItem;

};

#endif // __MSGNOTIFYUPDATEITEM_H__
