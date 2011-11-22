/*!
 * \file MsgNotifyIsSendLuckyChips.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyIsSendLuckyChips.h"

MsgNotifyIsSendLuckyChips::MsgNotifyIsSendLuckyChips()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyIsSendLuckyChips::~MsgNotifyIsSendLuckyChips()
{
	// TODO: 
}

bool MsgNotifyIsSendLuckyChips::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nIsSendLuckyChips, sizeof(nIsSendLuckyChips))) return false;
	return true;
}

bool MsgNotifyIsSendLuckyChips::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nIsSendLuckyChips, sizeof(nIsSendLuckyChips))) return false;
	return true;
}
