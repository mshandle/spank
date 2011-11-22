/*!
 * \file MsgAddRequest.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgAddRequest.h"

MsgAddRequest::MsgAddRequest()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgAddRequest::~MsgAddRequest()
{
	// TODO: 
}

bool MsgAddRequest::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nRequestId, sizeof(nRequestId))) return false;
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nFriendId, sizeof(nFriendId))) return false;
	if (!pReader->Read(&nRequestType, sizeof(nRequestType))) return false;
	if (!pReader->Read(&nPlatformId, sizeof(nPlatformId))) return false;
	if (!pReader->Read(&szNickName, sizeof(szNickName))) return false;
	if (!pReader->Read(&szPlatAccount, sizeof(szPlatAccount))) return false;
	return true;
}

bool MsgAddRequest::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nRequestId, sizeof(nRequestId))) return false;
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nFriendId, sizeof(nFriendId))) return false;
	if (!pWriter->Write(&nRequestType, sizeof(nRequestType))) return false;
	if (!pWriter->Write(&nPlatformId, sizeof(nPlatformId))) return false;
	if (!pWriter->Write(&szNickName, sizeof(szNickName))) return false;
	if (!pWriter->Write(&szPlatAccount, sizeof(szPlatAccount))) return false;
	return true;
}
