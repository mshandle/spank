/*!
 * \file MsgRequestSitDown.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestSitDown.h"

MsgRequestSitDown::MsgRequestSitDown()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestSitDown::~MsgRequestSitDown()
{
	// TODO: 
}

bool MsgRequestSitDown::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nBuyIn, sizeof(nBuyIn))) return false;
	return true;
}

bool MsgRequestSitDown::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nBuyIn, sizeof(nBuyIn))) return false;
	return true;
}
