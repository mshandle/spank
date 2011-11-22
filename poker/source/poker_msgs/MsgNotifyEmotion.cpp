/*!
 * \file MsgNotifyEmotion.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyEmotion.h"

MsgNotifyEmotion::MsgNotifyEmotion()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyEmotion::~MsgNotifyEmotion()
{
	// TODO: 
}

bool MsgNotifyEmotion::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nSeat, sizeof(nSeat))) return false;
	if (!pReader->Read(&nEmot, sizeof(nEmot))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgNotifyEmotion::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nSeat, sizeof(nSeat))) return false;
	if (!pWriter->Write(&nEmot, sizeof(nEmot))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
