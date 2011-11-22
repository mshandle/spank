/*!
 * \file MsgNotifyShootoutRank.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyShootoutRank.h"

MsgNotifyShootoutRank::MsgNotifyShootoutRank()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyShootoutRank::~MsgNotifyShootoutRank()
{
	// TODO: 
}

bool MsgNotifyShootoutRank::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nShootOutRank, sizeof(nShootOutRank))) return false;
	if (!pReader->Read(&_dummp, sizeof(_dummp))) return false;
	return true;
}

bool MsgNotifyShootoutRank::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nShootOutRank, sizeof(nShootOutRank))) return false;
	if (!pWriter->Write(&_dummp, sizeof(_dummp))) return false;
	return true;
}
