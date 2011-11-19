/*!
 * \file MsgNotifyBankupt.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyBankupt.h"

MsgNotifyBankupt::MsgNotifyBankupt()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyBankupt::~MsgNotifyBankupt()
{
	// TODO: 
}

bool MsgNotifyBankupt::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nProtectiveMoney, sizeof(nProtectiveMoney))) return false;
	if (!pReader->Read(&nTime, sizeof(nTime))) return false;
	return true;
}

bool MsgNotifyBankupt::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nProtectiveMoney, sizeof(nProtectiveMoney))) return false;
	if (!pWriter->Write(&nTime, sizeof(nTime))) return false;
	return true;
}
