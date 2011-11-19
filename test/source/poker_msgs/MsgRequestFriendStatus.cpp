/*!
 * \file MsgRequestFriendStatus.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestFriendStatus.h"

MsgRequestFriendStatus::MsgRequestFriendStatus()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestFriendStatus::~MsgRequestFriendStatus()
{
	// TODO: 
}

bool MsgRequestFriendStatus::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	return true;
}

bool MsgRequestFriendStatus::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	return true;
}
