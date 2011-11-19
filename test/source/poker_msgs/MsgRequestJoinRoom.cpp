/*!
 * \file MsgRequestJoinRoom.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestJoinRoom.h"

MsgRequestJoinRoom::MsgRequestJoinRoom()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestJoinRoom::~MsgRequestJoinRoom()
{
	// TODO: 
}

bool MsgRequestJoinRoom::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}

bool MsgRequestJoinRoom::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}
