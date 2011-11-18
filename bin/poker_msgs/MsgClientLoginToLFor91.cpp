/*!
 * \file MsgClientLoginToLFor91.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgClientLoginToLFor91.h"

MsgClientLoginToLFor91::MsgClientLoginToLFor91()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgClientLoginToLFor91::~MsgClientLoginToLFor91()
{
	// TODO: 
}

bool MsgClientLoginToLFor91::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&uid, sizeof(uid))) return false;
	if (!pReader->Read(&sessionId, sizeof(sessionId))) return false;
	return true;
}

bool MsgClientLoginToLFor91::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&uid, sizeof(uid))) return false;
	if (!pWriter->Write(&sessionId, sizeof(sessionId))) return false;
	return true;
}
