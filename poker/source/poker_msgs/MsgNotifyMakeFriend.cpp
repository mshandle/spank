/*!
 * \file MsgNotifyMakeFriend.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyMakeFriend.h"

MsgNotifyMakeFriend::MsgNotifyMakeFriend()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyMakeFriend::~MsgNotifyMakeFriend()
{
	// TODO: 
}

bool MsgNotifyMakeFriend::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSourceSeatId, sizeof(nSourceSeatId))) return false;
	if (!pReader->Read(&nDestSeatId, sizeof(nDestSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyMakeFriend::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSourceSeatId, sizeof(nSourceSeatId))) return false;
	if (!pWriter->Write(&nDestSeatId, sizeof(nDestSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
