/*!
 * \file MsgNotifyBet.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyBet.h"

MsgNotifyBet::MsgNotifyBet()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyBet::~MsgNotifyBet()
{
	// TODO: 
}

bool MsgNotifyBet::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&nTime, sizeof(nTime))) return false;
	if (!pReader->Read(&nTotalTime, sizeof(nTotalTime))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyBet::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&nTime, sizeof(nTime))) return false;
	if (!pWriter->Write(&nTotalTime, sizeof(nTotalTime))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
