/*!
 * \file NetDataType.h
 * \date 19-11-2011 17:09:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NETDATATYPE_H__
#define __NETDATATYPE_H__

#include <BaseType.h>

typedef struct NET_ITEM_INFO_tag
{
	int64 nItemId;		// 物品的数据库序列ID   -1: 表示空
	int nItemType;		// 物品Id 
	int64 nGiver;		// 赠送者
	int64 nObtainTime;	// 获得的时间
	int64 nExpireTime;	// 过期时间
} NET_ITEM_INFO;

typedef struct NET_USER_INFO_tag
{
	int64 nUserId;			// 当前包所属的玩家ID 以下属性都属于该ID
	int64 nCoins;			// 总资产
	int64 nMostCoins;		// 总资产的历史最高记录
	uchar nLevel;			// 等级
	uchar nIsVip;			// 是否VIP
	char _dummy[2];			// 补齐位
	uint nMuteTime;			// 累计在线时长
	uint nLogoutTime;		// 离线时间戳
} NET_USER_INFO;

typedef struct NET_ROOM_INFO_tag
{
	int nRoomId;			// -1=大厅
	char nPlayers;
	char nSeats;
	char nObservers;
	char nRoomType;
	int64 nSmallBlind;
	int64 nMinBuyIn;
	int64 nMaxBuyIn;
	int64 nDefaultBuyIn;	// 默认买入
	char nStatus;			// 状态: 0.stopping 1.running 
	char nTitleId;			// 第一段房间名ID, 所有类型房间都有, ShootOut和WeeklyTournament的都是0
	char nSubtitleId;		// 第二段房间名ID, 只有普通(快速)房间有, 其它类型房间为0
	char nSpecType;			// 房间类型
	int nTailNumber;		// 尾部号码, 所有房间都有
} NET_ROOM_INFO;

typedef struct NET_FRIEND_STATUS_tag
{
	int64 nFriendUserId;	// 好友玩家ID 
	char nStatus;			// 状态. 0: 大厅, 1: 普通/快速房间中, 2: Sit&Go房间中, 3: ShootOut房间中, 4: Weekly Tournament房间中
	char _dummy[3];
	NET_ROOM_INFO stRoomInfo;
} NET_FRIEND_STATUS;

typedef struct NET_REQUEST_DATA_tag
{
	int64 nRequestId;		// REQUEST的ID
	int64 nUserId;			// 发送REQUEST的玩家ID
	int64 nFriendId;		// 接收REQUEST的好友ID
	uint nRequestType;		// REQUEST类型
} NET_REQUEST_DATA;

typedef struct NET_SEAT_INFO_tag
{
	int64 nBet;				// 座上的赌注
	int64 nCounter;			// 携带的筹码
	int64 nUserId;			// 在座用户ID, -1:座位为空
	char nLastOp;			// -4:输光离开坐位 -3:正常离开坐位 -2: 刚坐下(没加入本局) -1:弃牌等待下一轮, 1:看牌, 2:跟注, 3:加注, 4:小盲注, 5:大盲注, 6 all in
	char _dummy[3];
	int nTrinket;			// 饰品
} NET_SEAT_INFO;

#endif // __NETDATATYPE_H__
