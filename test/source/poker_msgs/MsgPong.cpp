/*!
 * \file MsgPong.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgPong.h"

MsgPong::MsgPong()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgPong::~MsgPong()
{
	// TODO: 
}

bool MsgPong::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nId, sizeof(nId))) return false;
	if (!pReader->Read(&nTimestamp, sizeof(nTimestamp))) return false;
	return true;
}

bool MsgPong::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nId, sizeof(nId))) return false;
	if (!pWriter->Write(&nTimestamp, sizeof(nTimestamp))) return false;
	return true;
}
