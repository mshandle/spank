/*!
 * \file MsgNotifyTournamentStatus.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyTournamentStatus.h"

MsgNotifyTournamentStatus::MsgNotifyTournamentStatus()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyTournamentStatus::~MsgNotifyTournamentStatus()
{
	// TODO: 
}

bool MsgNotifyTournamentStatus::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRoomStatus, sizeof(nRoomStatus))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyTournamentStatus::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRoomStatus, sizeof(nRoomStatus))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
