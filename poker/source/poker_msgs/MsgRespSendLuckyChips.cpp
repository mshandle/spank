/*!
 * \file MsgRespSendLuckyChips.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespSendLuckyChips.h"

MsgRespSendLuckyChips::MsgRespSendLuckyChips()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespSendLuckyChips::~MsgRespSendLuckyChips()
{
	// TODO: 
}

bool MsgRespSendLuckyChips::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nLinkId, sizeof(nLinkId))) return false;
	if (!pReader->Read(&nType, sizeof(nType))) return false;
	return true;
}

bool MsgRespSendLuckyChips::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nLinkId, sizeof(nLinkId))) return false;
	if (!pWriter->Write(&nType, sizeof(nType))) return false;
	return true;
}
