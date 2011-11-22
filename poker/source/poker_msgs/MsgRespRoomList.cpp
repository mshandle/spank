/*!
 * \file MsgRespRoomList.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespRoomList.h"

MsgRespRoomList::MsgRespRoomList()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespRoomList::~MsgRespRoomList()
{
	// TODO: 
}

bool MsgRespRoomList::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nRoomNum, sizeof(nRoomNum))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&stRooms, sizeof(stRooms))) return false;
	return true;
}

bool MsgRespRoomList::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nRoomNum, sizeof(nRoomNum))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&stRooms, sizeof(stRooms))) return false;
	return true;
}
