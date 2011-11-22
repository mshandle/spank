/*!
 * \file MsgClientLoginToG.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgClientLoginToG.h"

MsgClientLoginToG::MsgClientLoginToG()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgClientLoginToG::~MsgClientLoginToG()
{
	// TODO: 
}

bool MsgClientLoginToG::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nSeqId, sizeof(nSeqId))) return false;
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&szCheckOutText, sizeof(szCheckOutText))) return false;
	if (!pReader->Read(&szSessionKey, sizeof(szSessionKey))) return false;
	if (!pReader->Read(&szSignInLocale, sizeof(szSignInLocale))) return false;
	return true;
}

bool MsgClientLoginToG::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nSeqId, sizeof(nSeqId))) return false;
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&szCheckOutText, sizeof(szCheckOutText))) return false;
	if (!pWriter->Write(&szSessionKey, sizeof(szSessionKey))) return false;
	if (!pWriter->Write(&szSignInLocale, sizeof(szSignInLocale))) return false;
	return true;
}
