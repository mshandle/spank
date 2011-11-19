/*!
 * \file MsgNotice.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotice.h"

MsgNotice::MsgNotice()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotice::~MsgNotice()
{
	// TODO: 
}

bool MsgNotice::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nType, sizeof(nType))) return false;
	if (!pReader->Read(&nArg1, sizeof(nArg1))) return false;
	if (!pReader->Read(&nArg2, sizeof(nArg2))) return false;
	if (!pReader->Read(&nTimestamp, sizeof(nTimestamp))) return false;
	return true;
}

bool MsgNotice::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nType, sizeof(nType))) return false;
	if (!pWriter->Write(&nArg1, sizeof(nArg1))) return false;
	if (!pWriter->Write(&nArg2, sizeof(nArg2))) return false;
	if (!pWriter->Write(&nTimestamp, sizeof(nTimestamp))) return false;
	return true;
}
