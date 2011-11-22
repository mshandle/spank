/*!
 * \file MsgSendGiftEnd.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgSendGiftEnd.h"

MsgSendGiftEnd::MsgSendGiftEnd()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgSendGiftEnd::~MsgSendGiftEnd()
{
	// TODO: 
}

bool MsgSendGiftEnd::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nTakerId, sizeof(nTakerId))) return false;
	if (!pReader->Read(&nItemType, sizeof(nItemType))) return false;
	return true;
}

bool MsgSendGiftEnd::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nTakerId, sizeof(nTakerId))) return false;
	if (!pWriter->Write(&nItemType, sizeof(nItemType))) return false;
	return true;
}
