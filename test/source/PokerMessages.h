/*!
 * \file PokerMessages.h
 * \date 11-15-2011 14:54:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __POKERMESSAGES_H__
#define __POKERMESSAGES_H__

#include <net/INetMsgBase.h>

class PokerMsgBase : public INetMsgBase
{
public:
	DECLARE_RTTI(PokerMsgBase, INetMsgBase);

	PokerMsgBase(short type, short size);
	virtual ~PokerMsgBase();

	short GetType() const;

	virtual bool FromStream(StreamReader* pReader);
	virtual bool ToStream(StreamWriter* pWriter);

	virtual bool Unpack(StreamReader* pReader) = 0;
	virtual bool Pack(StreamWriter* pWriter) = 0;

private:
	short m_Type;
	short m_Size;

};

class MsgClientLoginToLFor91 : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2600,
		MSG_SIZE = 52 + 128,
	};

public:
	DECLARE_RTTI(MsgClientLoginToLFor91, PokerMsgBase);

	MsgClientLoginToLFor91();
	virtual ~MsgClientLoginToLFor91();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char uid[52];
	char sessionId[128];

};

class MsgLoginServerValidate : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1004,
		MSG_SIZE = 8 + 16 + 4 + 24,
	};

public:
	DECLARE_RTTI(MsgLoginServerValidate, PokerMsgBase);

	MsgLoginServerValidate();
	virtual ~MsgLoginServerValidate();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	uint64 userID; // Facebook用户ID
	char ip[16]; // GameServer的IP地址
	int port; // GameServer端口
	char checkoutText[24]; // (二进制串，非字符串) LoginServer产生的验证串

};
#endif // __POKERMESSAGES_H__
