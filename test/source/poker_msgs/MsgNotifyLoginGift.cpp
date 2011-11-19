/*!
 * \file MsgNotifyLoginGift.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyLoginGift.h"

MsgNotifyLoginGift::MsgNotifyLoginGift()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyLoginGift::~MsgNotifyLoginGift()
{
	// TODO: 
}

bool MsgNotifyLoginGift::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nContinuousLogin, sizeof(nContinuousLogin))) return false;
	if (!pReader->Read(&nLastContinuousLogin, sizeof(nLastContinuousLogin))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&_dummy1, sizeof(_dummy1))) return false;
	return true;
}

bool MsgNotifyLoginGift::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nContinuousLogin, sizeof(nContinuousLogin))) return false;
	if (!pWriter->Write(&nLastContinuousLogin, sizeof(nLastContinuousLogin))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&_dummy1, sizeof(_dummy1))) return false;
	return true;
}
