/*!
 * \file MsgGameServerLoginResp.h
 * \date unknown
 * 
 * 登入GameServer消息返回
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGGAMESERVERLOGINRESP_H__
#define __MSGGAMESERVERLOGINRESP_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgGameServerLoginResp : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1005,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgGameServerLoginResp, PokerMsgBase);

	MsgGameServerLoginResp();
	virtual ~MsgGameServerLoginResp();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nLoginResult;	// 0: 登陆成功, 1: GameServer未开启, 2: GameServer连接已满, 3: UserServer未开启, 4: DbServer未开启, 5: 数据读取不完整, 6: ID已在登录中, 7: 验证失败, 8: 验证超时, 9: 用户未安装游戏(fql无permission项)
	int64 nUserId;
	int64 nIggId;

};

#endif // __MSGGAMESERVERLOGINRESP_H__
