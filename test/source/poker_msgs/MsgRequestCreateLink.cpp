/*!
 * \file MsgRequestCreateLink.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestCreateLink.h"

MsgRequestCreateLink::MsgRequestCreateLink()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestCreateLink::~MsgRequestCreateLink()
{
	// TODO: 
}

bool MsgRequestCreateLink::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nType, sizeof(nType))) return false;
	return true;
}

bool MsgRequestCreateLink::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nType, sizeof(nType))) return false;
	return true;
}
