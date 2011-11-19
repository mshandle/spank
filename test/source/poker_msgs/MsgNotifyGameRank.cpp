/*!
 * \file MsgNotifyGameRank.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyGameRank.h"

MsgNotifyGameRank::MsgNotifyGameRank()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyGameRank::~MsgNotifyGameRank()
{
	// TODO: 
}

bool MsgNotifyGameRank::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRank, sizeof(nRank))) return false;
	if (!pReader->Read(&nBonusType, sizeof(nBonusType))) return false;
	if (!pReader->Read(&nGameType, sizeof(nGameType))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nBonus, sizeof(nBonus))) return false;
	return true;
}

bool MsgNotifyGameRank::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRank, sizeof(nRank))) return false;
	if (!pWriter->Write(&nBonusType, sizeof(nBonusType))) return false;
	if (!pWriter->Write(&nGameType, sizeof(nGameType))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nBonus, sizeof(nBonus))) return false;
	return true;
}
