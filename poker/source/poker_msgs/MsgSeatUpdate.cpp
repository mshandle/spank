/*!
 * \file MsgSeatUpdate.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgSeatUpdate.h"

MsgSeatUpdate::MsgSeatUpdate()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgSeatUpdate::~MsgSeatUpdate()
{
	// TODO: 
}

bool MsgSeatUpdate::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&stSeatInfo, sizeof(stSeatInfo))) return false;
	return true;
}

bool MsgSeatUpdate::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&stSeatInfo, sizeof(stSeatInfo))) return false;
	return true;
}
