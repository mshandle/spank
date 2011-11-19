/*!
 * \file MsgRequestMakeFriend.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestMakeFriend.h"

MsgRequestMakeFriend::MsgRequestMakeFriend()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestMakeFriend::~MsgRequestMakeFriend()
{
	// TODO: 
}

bool MsgRequestMakeFriend::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nFriendUserId, sizeof(nFriendUserId))) return false;
	return true;
}

bool MsgRequestMakeFriend::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nFriendUserId, sizeof(nFriendUserId))) return false;
	return true;
}
