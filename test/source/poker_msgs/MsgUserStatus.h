/*!
 * \file MsgUserStatus.h
 * \date unknown
 * 
 * 告诉玩家当前的位置，可能有相应的原因
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUSERSTATUS_H__
#define __MSGUSERSTATUS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUserStatus : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2058,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgUserStatus, PokerMsgBase);

	MsgUserStatus();
	virtual ~MsgUserStatus();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nStatus;	// 位置信息, 0: 大厅, 1: 普通房间, 2: SitNGo房间, 3: MTT房间, 4: 周锦标赛房间
	char nReason;	// 相关提示, 0: 无提示, 1: 房间错误, 已离开房间, 2: MTT比赛结束/出局, 3: 房间人数已满, 4: 查无此房间, 无法进入, 5: MTT人数已满, 6: 周锦标赛人数已满 7: 自动选房失败, 8: 参数错误, 9: 资金不足, 10: RoomServer关闭, 11: 必须在大厅才可加入周锦标赛
	char _dummy[2];
	int nRoomId;	// 房间ID

};

#endif // __MSGUSERSTATUS_H__
