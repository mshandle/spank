/*!
 * \file MsgNotifyGameState.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyGameState.h"

MsgNotifyGameState::MsgNotifyGameState()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyGameState::~MsgNotifyGameState()
{
	// TODO: 
}

bool MsgNotifyGameState::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nBankerSeat, sizeof(nBankerSeat))) return false;
	if (!pReader->Read(&nSmallBlindSeat, sizeof(nSmallBlindSeat))) return false;
	if (!pReader->Read(&nBigBlindSeat, sizeof(nBigBlindSeat))) return false;
	if (!pReader->Read(&nGameStatus, sizeof(nGameStatus))) return false;
	if (!pReader->Read(&nRoomStatus, sizeof(nRoomStatus))) return false;
	if (!pReader->Read(&nHandCards, sizeof(nHandCards))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyGameState::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nBankerSeat, sizeof(nBankerSeat))) return false;
	if (!pWriter->Write(&nSmallBlindSeat, sizeof(nSmallBlindSeat))) return false;
	if (!pWriter->Write(&nBigBlindSeat, sizeof(nBigBlindSeat))) return false;
	if (!pWriter->Write(&nGameStatus, sizeof(nGameStatus))) return false;
	if (!pWriter->Write(&nRoomStatus, sizeof(nRoomStatus))) return false;
	if (!pWriter->Write(&nHandCards, sizeof(nHandCards))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
