/*!
 * \file MsgRespRoomList.h
 * \date unknown
 * 
 * 客户端房间列表请求的应答
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPROOMLIST_H__
#define __MSGRESPROOMLIST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespRoomList : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2003,
		MSG_SIZE = 1252,
	};

public:
	DECLARE_RTTI(MsgRespRoomList, PokerMsgBase);

	MsgRespRoomList();
	virtual ~MsgRespRoomList();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	short nRoomNum;
	char _dummy[2];	// 补齐位
	NET_ROOM_INFO stRooms[26];

};

#endif // __MSGRESPROOMLIST_H__
