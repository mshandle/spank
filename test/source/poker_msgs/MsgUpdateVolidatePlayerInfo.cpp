/*!
 * \file MsgUpdateVolidatePlayerInfo.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgUpdateVolidatePlayerInfo.h"

MsgUpdateVolidatePlayerInfo::MsgUpdateVolidatePlayerInfo()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgUpdateVolidatePlayerInfo::~MsgUpdateVolidatePlayerInfo()
{
	// TODO: 
}

bool MsgUpdateVolidatePlayerInfo::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nLevel, sizeof(nLevel))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nCoins, sizeof(nCoins))) return false;
	if (!pReader->Read(&nWinThisWeek, sizeof(nWinThisWeek))) return false;
	if (!pReader->Read(&nCash, sizeof(nCash))) return false;
	if (!pReader->Read(&nExp, sizeof(nExp))) return false;
	if (!pReader->Read(&nTrinket, sizeof(nTrinket))) return false;
	return true;
}

bool MsgUpdateVolidatePlayerInfo::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nLevel, sizeof(nLevel))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nCoins, sizeof(nCoins))) return false;
	if (!pWriter->Write(&nWinThisWeek, sizeof(nWinThisWeek))) return false;
	if (!pWriter->Write(&nCash, sizeof(nCash))) return false;
	if (!pWriter->Write(&nExp, sizeof(nExp))) return false;
	if (!pWriter->Write(&nTrinket, sizeof(nTrinket))) return false;
	return true;
}
