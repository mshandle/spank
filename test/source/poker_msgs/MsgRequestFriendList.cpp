/*!
 * \file MsgRequestFriendList.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestFriendList.h"

MsgRequestFriendList::MsgRequestFriendList()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestFriendList::~MsgRequestFriendList()
{
	// TODO: 
}

bool MsgRequestFriendList::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	return true;
}

bool MsgRequestFriendList::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	return true;
}
