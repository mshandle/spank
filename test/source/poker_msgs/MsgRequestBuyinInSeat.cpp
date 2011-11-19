/*!
 * \file MsgRequestBuyinInSeat.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestBuyinInSeat.h"

MsgRequestBuyinInSeat::MsgRequestBuyinInSeat()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestBuyinInSeat::~MsgRequestBuyinInSeat()
{
	// TODO: 
}

bool MsgRequestBuyinInSeat::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nBuyIn, sizeof(nBuyIn))) return false;
	return true;
}

bool MsgRequestBuyinInSeat::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nBuyIn, sizeof(nBuyIn))) return false;
	return true;
}
