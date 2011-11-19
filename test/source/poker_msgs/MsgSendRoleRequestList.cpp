/*!
 * \file MsgSendRoleRequestList.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgSendRoleRequestList.h"

MsgSendRoleRequestList::MsgSendRoleRequestList()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgSendRoleRequestList::~MsgSendRoleRequestList()
{
	// TODO: 
}

bool MsgSendRoleRequestList::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&UserId, sizeof(UserId))) return false;
	if (!pReader->Read(&bTail, sizeof(bTail))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&stRequestList, sizeof(stRequestList))) return false;
	return true;
}

bool MsgSendRoleRequestList::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&UserId, sizeof(UserId))) return false;
	if (!pWriter->Write(&bTail, sizeof(bTail))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&stRequestList, sizeof(stRequestList))) return false;
	return true;
}
