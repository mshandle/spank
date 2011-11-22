/*!
 * \file MsgRequestReceiveLoginGift.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestReceiveLoginGift.h"

MsgRequestReceiveLoginGift::MsgRequestReceiveLoginGift()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestReceiveLoginGift::~MsgRequestReceiveLoginGift()
{
	// TODO: 
}

bool MsgRequestReceiveLoginGift::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nChoice, sizeof(nChoice))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgRequestReceiveLoginGift::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nChoice, sizeof(nChoice))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
