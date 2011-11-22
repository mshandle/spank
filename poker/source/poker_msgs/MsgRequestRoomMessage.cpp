/*!
 * \file MsgRequestRoomMessage.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestRoomMessage.h"

MsgRequestRoomMessage::MsgRequestRoomMessage()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestRoomMessage::~MsgRequestRoomMessage()
{
	// TODO: 
}

bool MsgRequestRoomMessage::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nMsgLength, sizeof(nMsgLength))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nDest, sizeof(nDest))) return false;
	if (!pReader->Read(&szMessage, sizeof(szMessage))) return false;
	return true;
}

bool MsgRequestRoomMessage::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nMsgLength, sizeof(nMsgLength))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nDest, sizeof(nDest))) return false;
	if (!pWriter->Write(&szMessage, sizeof(szMessage))) return false;
	return true;
}
