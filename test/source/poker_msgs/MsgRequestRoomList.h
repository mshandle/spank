/*!
 * \file MsgRequestRoomList.h
 * \date unknown
 * 
 * 客户端请求房间列表
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTROOMLIST_H__
#define __MSGREQUESTROOMLIST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestRoomList : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2002,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestRoomList, PokerMsgBase);

	MsgRequestRoomList();
	virtual ~MsgRequestRoomList();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nRoomType;	// 0: 普通房, 6: 快速房, 10: Sit  Go房间, 11: 快速Sit  Go房间, 

};

#endif // __MSGREQUESTROOMLIST_H__
