/*!
 * \file PokerMsgBase.cpp
 * \date 11-17-2011 16:14:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PokerMsgBase.h"
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
