/*!
 * \file MsgNotifySmallBlind.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifySmallBlind.h"

MsgNotifySmallBlind::MsgNotifySmallBlind()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifySmallBlind::~MsgNotifySmallBlind()
{
	// TODO: 
}

bool MsgNotifySmallBlind::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSmallBlind, sizeof(nSmallBlind))) return false;
	return true;
}

bool MsgNotifySmallBlind::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSmallBlind, sizeof(nSmallBlind))) return false;
	return true;
}
