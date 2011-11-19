/*!
 * \file MsgRequestAcceptFriend.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestAcceptFriend.h"

MsgRequestAcceptFriend::MsgRequestAcceptFriend()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestAcceptFriend::~MsgRequestAcceptFriend()
{
	// TODO: 
}

bool MsgRequestAcceptFriend::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSourceSeatId, sizeof(nSourceSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgRequestAcceptFriend::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSourceSeatId, sizeof(nSourceSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
