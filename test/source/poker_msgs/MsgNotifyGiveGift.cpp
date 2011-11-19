/*!
 * \file MsgNotifyGiveGift.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyGiveGift.h"

MsgNotifyGiveGift::MsgNotifyGiveGift()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyGiveGift::~MsgNotifyGiveGift()
{
	// TODO: 
}

bool MsgNotifyGiveGift::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nItemType, sizeof(nItemType))) return false;
	if (!pReader->Read(&nGiverId, sizeof(nGiverId))) return false;
	if (!pReader->Read(&nTakerId, sizeof(nTakerId))) return false;
	if (!pReader->Read(&nGiveSeatId, sizeof(nGiveSeatId))) return false;
	if (!pReader->Read(&nTakerSeatId, sizeof(nTakerSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyGiveGift::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nItemType, sizeof(nItemType))) return false;
	if (!pWriter->Write(&nGiverId, sizeof(nGiverId))) return false;
	if (!pWriter->Write(&nTakerId, sizeof(nTakerId))) return false;
	if (!pWriter->Write(&nGiveSeatId, sizeof(nGiveSeatId))) return false;
	if (!pWriter->Write(&nTakerSeatId, sizeof(nTakerSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
