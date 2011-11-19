/*!
 * \file MsgNotifyUpdateItem.h
 * \date unknown
 * 
 * 
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
	char nType;
	char _dummy[3];
	NET_ITEM_INFO stItem;

};

#endif // __MSGNOTIFYUPDATEITEM_H__
