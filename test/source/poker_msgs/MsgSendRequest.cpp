/*!
 * \file MsgSendRequest.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgSendRequest.h"

MsgSendRequest::MsgSendRequest()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgSendRequest::~MsgSendRequest()
{
	// TODO: 
}

bool MsgSendRequest::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pReader->Read(&nRType, sizeof(nRType))) return false;
	return true;
}

bool MsgSendRequest::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pWriter->Write(&nRType, sizeof(nRType))) return false;
	return true;
}
