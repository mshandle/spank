/*!
 * \file MsgRoomInfo.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRoomInfo.h"

MsgRoomInfo::MsgRoomInfo()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRoomInfo::~MsgRoomInfo()
{
	// TODO: 
}

bool MsgRoomInfo::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&stRoomInfo, sizeof(stRoomInfo))) return false;
	if (!pReader->Read(&stSeats, sizeof(stSeats))) return false;
	if (!pReader->Read(&nBanker, sizeof(nBanker))) return false;
	if (!pReader->Read(&nSmallBlind, sizeof(nSmallBlind))) return false;
	if (!pReader->Read(&nBigBlind, sizeof(nBigBlind))) return false;
	if (!pReader->Read(&nPublicCards, sizeof(nPublicCards))) return false;
	if (!pReader->Read(&nPools, sizeof(nPools))) return false;
	if (!pReader->Read(&nHandCards, sizeof(nHandCards))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgRoomInfo::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&stRoomInfo, sizeof(stRoomInfo))) return false;
	if (!pWriter->Write(&stSeats, sizeof(stSeats))) return false;
	if (!pWriter->Write(&nBanker, sizeof(nBanker))) return false;
	if (!pWriter->Write(&nSmallBlind, sizeof(nSmallBlind))) return false;
	if (!pWriter->Write(&nBigBlind, sizeof(nBigBlind))) return false;
	if (!pWriter->Write(&nPublicCards, sizeof(nPublicCards))) return false;
	if (!pWriter->Write(&nPools, sizeof(nPools))) return false;
	if (!pWriter->Write(&nHandCards, sizeof(nHandCards))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
