/*!
 * \file MsgRequestRoomMembers.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestRoomMembers.h"

MsgRequestRoomMembers::MsgRequestRoomMembers()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestRoomMembers::~MsgRequestRoomMembers()
{
	// TODO: 
}

bool MsgRequestRoomMembers::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRoomId, sizeof(nRoomId))) return false;
	if (!pReader->Read(&nMemberType, sizeof(nMemberType))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgRequestRoomMembers::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRoomId, sizeof(nRoomId))) return false;
	if (!pWriter->Write(&nMemberType, sizeof(nMemberType))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
