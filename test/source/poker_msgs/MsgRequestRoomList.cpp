/*!
 * \file MsgRequestRoomList.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestRoomList.h"

MsgRequestRoomList::MsgRequestRoomList()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestRoomList::~MsgRequestRoomList()
{
	// TODO: 
}

bool MsgRequestRoomList::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRoomType, sizeof(nRoomType))) return false;
	return true;
}

bool MsgRequestRoomList::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRoomType, sizeof(nRoomType))) return false;
	return true;
}
