/*!
 * \file MsgNotifyRoomMessage.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyRoomMessage.h"

MsgNotifyRoomMessage::MsgNotifyRoomMessage()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyRoomMessage::~MsgNotifyRoomMessage()
{
	// TODO: 
}

bool MsgNotifyRoomMessage::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSenderUserId, sizeof(nSenderUserId))) return false;
	if (!pReader->Read(&nMsgLength, sizeof(nMsgLength))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nDest, sizeof(nDest))) return false;
	if (!pReader->Read(&nMessage, sizeof(nMessage))) return false;
	return true;
}

bool MsgNotifyRoomMessage::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSenderUserId, sizeof(nSenderUserId))) return false;
	if (!pWriter->Write(&nMsgLength, sizeof(nMsgLength))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nDest, sizeof(nDest))) return false;
	if (!pWriter->Write(&nMessage, sizeof(nMessage))) return false;
	return true;
}
