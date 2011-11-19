/*!
 * \file MsgInitPlayerInfo.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgInitPlayerInfo.h"

MsgInitPlayerInfo::MsgInitPlayerInfo()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgInitPlayerInfo::~MsgInitPlayerInfo()
{
	// TODO: 
}

bool MsgInitPlayerInfo::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nLevel, sizeof(nLevel))) return false;
	if (!pReader->Read(&nFlags, sizeof(nFlags))) return false;
	if (!pReader->Read(&nShootOutRank, sizeof(nShootOutRank))) return false;
	if (!pReader->Read(&nShootOutPlace, sizeof(nShootOutPlace))) return false;
	if (!pReader->Read(&nCoins, sizeof(nCoins))) return false;
	if (!pReader->Read(&nMostCoins, sizeof(nMostCoins))) return false;
	if (!pReader->Read(&nWinThisWeek, sizeof(nWinThisWeek))) return false;
	if (!pReader->Read(&nCash, sizeof(nCash))) return false;
	if (!pReader->Read(&nExp, sizeof(nExp))) return false;
	if (!pReader->Read(&nChampionInBuddiesLastWeek, sizeof(nChampionInBuddiesLastWeek))) return false;
	if (!pReader->Read(&nMostWinInBuddiesLastWeek, sizeof(nMostWinInBuddiesLastWeek))) return false;
	if (!pReader->Read(&nTrinket, sizeof(nTrinket))) return false;
	if (!pReader->Read(&nTutorialFlags, sizeof(nTutorialFlags))) return false;
	return true;
}

bool MsgInitPlayerInfo::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nLevel, sizeof(nLevel))) return false;
	if (!pWriter->Write(&nFlags, sizeof(nFlags))) return false;
	if (!pWriter->Write(&nShootOutRank, sizeof(nShootOutRank))) return false;
	if (!pWriter->Write(&nShootOutPlace, sizeof(nShootOutPlace))) return false;
	if (!pWriter->Write(&nCoins, sizeof(nCoins))) return false;
	if (!pWriter->Write(&nMostCoins, sizeof(nMostCoins))) return false;
	if (!pWriter->Write(&nWinThisWeek, sizeof(nWinThisWeek))) return false;
	if (!pWriter->Write(&nCash, sizeof(nCash))) return false;
	if (!pWriter->Write(&nExp, sizeof(nExp))) return false;
	if (!pWriter->Write(&nChampionInBuddiesLastWeek, sizeof(nChampionInBuddiesLastWeek))) return false;
	if (!pWriter->Write(&nMostWinInBuddiesLastWeek, sizeof(nMostWinInBuddiesLastWeek))) return false;
	if (!pWriter->Write(&nTrinket, sizeof(nTrinket))) return false;
	if (!pWriter->Write(&nTutorialFlags, sizeof(nTutorialFlags))) return false;
	return true;
}
