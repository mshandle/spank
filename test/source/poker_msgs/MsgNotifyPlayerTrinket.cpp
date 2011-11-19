/*!
 * \file MsgNotifyPlayerTrinket.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyPlayerTrinket.h"

MsgNotifyPlayerTrinket::MsgNotifyPlayerTrinket()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyPlayerTrinket::~MsgNotifyPlayerTrinket()
{
	// TODO: 
}

bool MsgNotifyPlayerTrinket::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nTrinket, sizeof(nTrinket))) return false;
	if (!pReader->Read(&nSourceUserId, sizeof(nSourceUserId))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyPlayerTrinket::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nTrinket, sizeof(nTrinket))) return false;
	if (!pWriter->Write(&nSourceUserId, sizeof(nSourceUserId))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
