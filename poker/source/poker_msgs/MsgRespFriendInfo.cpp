/*!
 * \file MsgRespFriendInfo.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespFriendInfo.h"

MsgRespFriendInfo::MsgRespFriendInfo()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespFriendInfo::~MsgRespFriendInfo()
{
	// TODO: 
}

bool MsgRespFriendInfo::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pReader->Read(&nInFacebook, sizeof(nInFacebook))) return false;
	if (!pReader->Read(&nLevel, sizeof(nLevel))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nCoins, sizeof(nCoins))) return false;
	if (!pReader->Read(&nMostCoins, sizeof(nMostCoins))) return false;
	if (!pReader->Read(&nCash, sizeof(nCash))) return false;
	if (!pReader->Read(&nLogoutTime, sizeof(nLogoutTime))) return false;
	if (!pReader->Read(&nWinThisWeek, sizeof(nWinThisWeek))) return false;
	return true;
}

bool MsgRespFriendInfo::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pWriter->Write(&nInFacebook, sizeof(nInFacebook))) return false;
	if (!pWriter->Write(&nLevel, sizeof(nLevel))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nCoins, sizeof(nCoins))) return false;
	if (!pWriter->Write(&nMostCoins, sizeof(nMostCoins))) return false;
	if (!pWriter->Write(&nCash, sizeof(nCash))) return false;
	if (!pWriter->Write(&nLogoutTime, sizeof(nLogoutTime))) return false;
	if (!pWriter->Write(&nWinThisWeek, sizeof(nWinThisWeek))) return false;
	return true;
}
