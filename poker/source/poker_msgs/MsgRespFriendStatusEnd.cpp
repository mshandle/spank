/*!
 * \file MsgRespFriendStatusEnd.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespFriendStatusEnd.h"

MsgRespFriendStatusEnd::MsgRespFriendStatusEnd()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespFriendStatusEnd::~MsgRespFriendStatusEnd()
{
	// TODO: 
}

bool MsgRespFriendStatusEnd::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	return true;
}

bool MsgRespFriendStatusEnd::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	return true;
}
