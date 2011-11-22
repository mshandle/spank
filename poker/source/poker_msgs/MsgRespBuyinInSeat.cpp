/*!
 * \file MsgRespBuyinInSeat.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespBuyinInSeat.h"

MsgRespBuyinInSeat::MsgRespBuyinInSeat()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespBuyinInSeat::~MsgRespBuyinInSeat()
{
	// TODO: 
}

bool MsgRespBuyinInSeat::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nStatus, sizeof(nStatus))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgRespBuyinInSeat::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nStatus, sizeof(nStatus))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
