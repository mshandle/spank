/*!
 * \file MsgRespRoomMembers.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespRoomMembers.h"

MsgRespRoomMembers::MsgRespRoomMembers()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespRoomMembers::~MsgRespRoomMembers()
{
	// TODO: 
}

bool MsgRespRoomMembers::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRoomId, sizeof(nRoomId))) return false;
	if (!pReader->Read(&nMemberType, sizeof(nMemberType))) return false;
	if (!pReader->Read(&nMemberNum, sizeof(nMemberNum))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&stMembers, sizeof(stMembers))) return false;
	return true;
}

bool MsgRespRoomMembers::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRoomId, sizeof(nRoomId))) return false;
	if (!pWriter->Write(&nMemberType, sizeof(nMemberType))) return false;
	if (!pWriter->Write(&nMemberNum, sizeof(nMemberNum))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&stMembers, sizeof(stMembers))) return false;
	return true;
}
