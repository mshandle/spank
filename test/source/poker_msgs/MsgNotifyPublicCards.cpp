/*!
 * \file MsgNotifyPublicCards.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyPublicCards.h"

MsgNotifyPublicCards::MsgNotifyPublicCards()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyPublicCards::~MsgNotifyPublicCards()
{
	// TODO: 
}

bool MsgNotifyPublicCards::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nCount, sizeof(nCount))) return false;
	if (!pReader->Read(&nCards, sizeof(nCards))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyPublicCards::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nCount, sizeof(nCount))) return false;
	if (!pWriter->Write(&nCards, sizeof(nCards))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
