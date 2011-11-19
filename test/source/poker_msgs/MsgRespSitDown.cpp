/*!
 * \file MsgRespSitDown.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespSitDown.h"

MsgRespSitDown::MsgRespSitDown()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespSitDown::~MsgRespSitDown()
{
	// TODO: 
}

bool MsgRespSitDown::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRoomId, sizeof(nRoomId))) return false;
	if (!pReader->Read(&nSeatId, sizeof(nSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nCounter, sizeof(nCounter))) return false;
	return true;
}

bool MsgRespSitDown::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRoomId, sizeof(nRoomId))) return false;
	if (!pWriter->Write(&nSeatId, sizeof(nSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nCounter, sizeof(nCounter))) return false;
	return true;
}
