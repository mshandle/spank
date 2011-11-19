/*!
 * \file MsgRespReceiveLoginGift.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespReceiveLoginGift.h"

MsgRespReceiveLoginGift::MsgRespReceiveLoginGift()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespReceiveLoginGift::~MsgRespReceiveLoginGift()
{
	// TODO: 
}

bool MsgRespReceiveLoginGift::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nResult, sizeof(nResult))) return false;
	if (!pReader->Read(&nChoice, sizeof(nChoice))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nPots, sizeof(nPots))) return false;
	if (!pReader->Read(&nBonus, sizeof(nBonus))) return false;
	return true;
}

bool MsgRespReceiveLoginGift::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nResult, sizeof(nResult))) return false;
	if (!pWriter->Write(&nChoice, sizeof(nChoice))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nPots, sizeof(nPots))) return false;
	if (!pWriter->Write(&nBonus, sizeof(nBonus))) return false;
	return true;
}
