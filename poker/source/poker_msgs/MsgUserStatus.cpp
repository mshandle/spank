/*!
 * \file MsgUserStatus.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgUserStatus.h"

MsgUserStatus::MsgUserStatus()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgUserStatus::~MsgUserStatus()
{
	// TODO: 
}

bool MsgUserStatus::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nStatus, sizeof(nStatus))) return false;
	if (!pReader->Read(&nReason, sizeof(nReason))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}

bool MsgUserStatus::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nStatus, sizeof(nStatus))) return false;
	if (!pWriter->Write(&nReason, sizeof(nReason))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nRoomId, sizeof(nRoomId))) return false;
	return true;
}
