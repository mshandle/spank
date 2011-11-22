/*!
 * \file MsgClientLoginToL.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgClientLoginToL.h"

MsgClientLoginToL::MsgClientLoginToL()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgClientLoginToL::~MsgClientLoginToL()
{
	// TODO: 
}

bool MsgClientLoginToL::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nSeqId, sizeof(nSeqId))) return false;
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&szSessionKey, sizeof(szSessionKey))) return false;
	if (!pReader->Read(&szLoginSessionKey, sizeof(szLoginSessionKey))) return false;
	if (!pReader->Read(&szLoginPassWord, sizeof(szLoginPassWord))) return false;
	if (!pReader->Read(&nGroupId, sizeof(nGroupId))) return false;
	return true;
}

bool MsgClientLoginToL::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nSeqId, sizeof(nSeqId))) return false;
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&szSessionKey, sizeof(szSessionKey))) return false;
	if (!pWriter->Write(&szLoginSessionKey, sizeof(szLoginSessionKey))) return false;
	if (!pWriter->Write(&szLoginPassWord, sizeof(szLoginPassWord))) return false;
	if (!pWriter->Write(&nGroupId, sizeof(nGroupId))) return false;
	return true;
}
