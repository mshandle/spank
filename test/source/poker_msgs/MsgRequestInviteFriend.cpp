/*!
 * \file MsgRequestInviteFriend.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestInviteFriend.h"

MsgRequestInviteFriend::MsgRequestInviteFriend()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestInviteFriend::~MsgRequestInviteFriend()
{
	// TODO: 
}

bool MsgRequestInviteFriend::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pReader->Read(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}

bool MsgRequestInviteFriend::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pWriter->Write(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}
