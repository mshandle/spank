/*!
 * \file MsgNotifyPlayerInRoom.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyPlayerInRoom.h"

MsgNotifyPlayerInRoom::MsgNotifyPlayerInRoom()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyPlayerInRoom::~MsgNotifyPlayerInRoom()
{
	// TODO: 
}

bool MsgNotifyPlayerInRoom::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSourceUserId, sizeof(nSourceUserId))) return false;
	if (!pReader->Read(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}

bool MsgNotifyPlayerInRoom::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSourceUserId, sizeof(nSourceUserId))) return false;
	if (!pWriter->Write(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}
