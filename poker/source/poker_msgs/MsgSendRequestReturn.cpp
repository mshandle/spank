/*!
 * \file MsgSendRequestReturn.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgSendRequestReturn.h"

MsgSendRequestReturn::MsgSendRequestReturn()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgSendRequestReturn::~MsgSendRequestReturn()
{
	// TODO: 
}

bool MsgSendRequestReturn::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pReader->Read(&nRequestId, sizeof(nRequestId))) return false;
	if (!pReader->Read(&unRequestType, sizeof(unRequestType))) return false;
	if (!pReader->Read(&nPlatformId, sizeof(nPlatformId))) return false;
	if (!pReader->Read(&szNickName, sizeof(szNickName))) return false;
	if (!pReader->Read(&szPlatformAccount, sizeof(szPlatformAccount))) return false;
	return true;
}

bool MsgSendRequestReturn::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nFriendUserId, sizeof(nFriendUserId))) return false;
	if (!pWriter->Write(&nRequestId, sizeof(nRequestId))) return false;
	if (!pWriter->Write(&unRequestType, sizeof(unRequestType))) return false;
	if (!pWriter->Write(&nPlatformId, sizeof(nPlatformId))) return false;
	if (!pWriter->Write(&szNickName, sizeof(szNickName))) return false;
	if (!pWriter->Write(&szPlatformAccount, sizeof(szPlatformAccount))) return false;
	return true;
}
