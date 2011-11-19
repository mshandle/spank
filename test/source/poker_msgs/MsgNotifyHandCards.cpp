/*!
 * \file MsgNotifyHandCards.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyHandCards.h"

MsgNotifyHandCards::MsgNotifyHandCards()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyHandCards::~MsgNotifyHandCards()
{
	// TODO: 
}

bool MsgNotifyHandCards::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&nCards, sizeof(nCards))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyHandCards::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&nCards, sizeof(nCards))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
