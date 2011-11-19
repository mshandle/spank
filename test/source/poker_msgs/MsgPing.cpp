/*!
 * \file MsgPing.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgPing.h"

MsgPing::MsgPing()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgPing::~MsgPing()
{
	// TODO: 
}

bool MsgPing::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nId, sizeof(nId))) return false;
	if (!pReader->Read(&nTimestamp, sizeof(nTimestamp))) return false;
	return true;
}

bool MsgPing::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nId, sizeof(nId))) return false;
	if (!pWriter->Write(&nTimestamp, sizeof(nTimestamp))) return false;
	return true;
}
