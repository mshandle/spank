/*!
 * \file MsgRespAcceptFreeChips.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespAcceptFreeChips.h"

MsgRespAcceptFreeChips::MsgRespAcceptFreeChips()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespAcceptFreeChips::~MsgRespAcceptFreeChips()
{
	// TODO: 
}

bool MsgRespAcceptFreeChips::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nResult, sizeof(nResult))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nRequsetId, sizeof(nRequsetId))) return false;
	if (!pReader->Read(&nGeneratedChips, sizeof(nGeneratedChips))) return false;
	return true;
}

bool MsgRespAcceptFreeChips::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nResult, sizeof(nResult))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nRequsetId, sizeof(nRequsetId))) return false;
	if (!pWriter->Write(&nGeneratedChips, sizeof(nGeneratedChips))) return false;
	return true;
}
