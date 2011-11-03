/*!
 * \file MsgKey.cpp
 * \date 11-03-2011 15:36:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgKey.h>
#include <msg/MsgID.h>

MsgKey::MsgKey(KEY_TYPE eType)
:IMsgBase(MI_KEY)
{
	m_eKeyType = eType;
}

MsgKey::~MsgKey()
{
	// TODO: 
}

MsgKey::KEY_TYPE MsgKey::GetKeyType()
{
	return m_eKeyType;
}

bool MsgKey::IsHome() const
{
	return (m_eKeyType == KT_HOME);
}

bool MsgKey::IsReturn() const
{
	return (m_eKeyType == KT_RETURN);
}
