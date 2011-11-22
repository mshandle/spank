/*!
 * \file MsgRespFriendStatus.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespFriendStatus.h"

MsgRespFriendStatus::MsgRespFriendStatus()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespFriendStatus::~MsgRespFriendStatus()
{
	// TODO: 
}

bool MsgRespFriendStatus::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nCount, sizeof(nCount))) return false;
	if (!pReader->Read(&stFriends, sizeof(stFriends))) return false;
	return true;
}

bool MsgRespFriendStatus::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nCount, sizeof(nCount))) return false;
	if (!pWriter->Write(&stFriends, sizeof(stFriends))) return false;
	return true;
}
