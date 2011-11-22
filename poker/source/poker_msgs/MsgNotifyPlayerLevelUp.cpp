/*!
 * \file MsgNotifyPlayerLevelUp.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyPlayerLevelUp.h"

MsgNotifyPlayerLevelUp::MsgNotifyPlayerLevelUp()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyPlayerLevelUp::~MsgNotifyPlayerLevelUp()
{
	// TODO: 
}

bool MsgNotifyPlayerLevelUp::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nLevel, sizeof(nLevel))) return false;
	if (!pReader->Read(&nExp, sizeof(nExp))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyPlayerLevelUp::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nLevel, sizeof(nLevel))) return false;
	if (!pWriter->Write(&nExp, sizeof(nExp))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
