/*!
 * \file MsgRequestDeleteFriend.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestDeleteFriend.h"

MsgRequestDeleteFriend::MsgRequestDeleteFriend()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestDeleteFriend::~MsgRequestDeleteFriend()
{
	// TODO: 
}

bool MsgRequestDeleteFriend::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nFriendUserId, sizeof(nFriendUserId))) return false;
	return true;
}

bool MsgRequestDeleteFriend::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nFriendUserId, sizeof(nFriendUserId))) return false;
	return true;
}
