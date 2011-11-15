/*!
 * \file PokerMessages.cpp
 * \date 11-15-2011 14:54:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PokerMessages.h"
#include <util/StringUtil.h>
#include <util/IDebugUtil.h>

PokerMsgBase::PokerMsgBase(short type, short size)
{
	m_Type = type;
	m_Size = size + sizeof(m_Type) + sizeof(m_Size);
}

PokerMsgBase::~PokerMsgBase()
{
	// TODO: 
}

short PokerMsgBase::GetType() const
{
	return m_Type;
}

bool PokerMsgBase::FromStream(StreamReader* pReader)
{
	short size = 0;
	if (!pReader->Read(&size, sizeof(size))) return false;
	if (size != m_Size)
	{
		LOGE("message size miss-match: server:%d, client:%d", size, m_Size);
		return false;
	}

	short type = 0;
	if (!pReader->Read(&type, sizeof(type))) return false;
	if (type != m_Type)
	{
		LOGE("message type miss-match: server:%d, client:%d", type, m_Type);
		return false;
	}

	return Unpack(pReader);
}

bool PokerMsgBase::ToStream(StreamWriter* pWriter)
{
	if (!pWriter->Write(&m_Size, sizeof(m_Size))) return false;
	if (!pWriter->Write(&m_Type, sizeof(m_Type))) return false;

	return Pack(pWriter);
}

MsgClientLoginToLFor91::MsgClientLoginToLFor91()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	StringUtil::ZeroMemory(&uid, sizeof(uid));
	StringUtil::ZeroMemory(&sessionId, sizeof(sessionId));
}

MsgClientLoginToLFor91::~MsgClientLoginToLFor91()
{
	// TODO: 
}

bool MsgClientLoginToLFor91::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&uid, sizeof(uid))) return false;
	if (!pReader->Read(&sessionId, sizeof(sessionId))) return false;
	return true;
}

bool MsgClientLoginToLFor91::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&uid, sizeof(uid))) return false;
	if (!pWriter->Write(&sessionId, sizeof(sessionId))) return false;
	return true;
}

MsgLoginServerValidate::MsgLoginServerValidate()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	userID = 0; // Facebook用户ID
	StringUtil::ZeroMemory(ip, sizeof(ip)); // GameServer的IP地址
	port = 0; // GameServer端口
	StringUtil::ZeroMemory(checkoutText, sizeof(checkoutText)); // (二进制串，非字符串) LoginServer产生的验证串
}

MsgLoginServerValidate::~MsgLoginServerValidate()
{
	// TODO: 
}

bool MsgLoginServerValidate::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&userID, sizeof(userID))) return false;
	if (!pReader->Read(&ip, sizeof(ip))) return false;
	if (!pReader->Read(&port, sizeof(port))) return false;
	if (!pReader->Read(&checkoutText, sizeof(checkoutText))) return false;
	return true;
}

bool MsgLoginServerValidate::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&userID, sizeof(userID))) return false;
	if (!pWriter->Write(&ip, sizeof(ip))) return false;
	if (!pWriter->Write(&port, sizeof(port))) return false;
	if (!pWriter->Write(&checkoutText, sizeof(checkoutText))) return false;
	return true;
}
