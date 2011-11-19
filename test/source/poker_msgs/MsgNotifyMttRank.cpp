/*!
 * \file MsgNotifyMttRank.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyMttRank.h"

MsgNotifyMttRank::MsgNotifyMttRank()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyMttRank::~MsgNotifyMttRank()
{
	// TODO: 
}

bool MsgNotifyMttRank::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nRank, sizeof(nRank))) return false;
	if (!pReader->Read(&nBonus, sizeof(nBonus))) return false;
	return true;
}

bool MsgNotifyMttRank::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nRank, sizeof(nRank))) return false;
	if (!pWriter->Write(&nBonus, sizeof(nBonus))) return false;
	return true;
}
