/*!
 * \file MsgGameServerLoginResp.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgGameServerLoginResp.h"

MsgGameServerLoginResp::MsgGameServerLoginResp()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgGameServerLoginResp::~MsgGameServerLoginResp()
{
	// TODO: 
}

bool MsgGameServerLoginResp::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nLoginResult, sizeof(nLoginResult))) return false;
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nIggId, sizeof(nIggId))) return false;
	return true;
}

bool MsgGameServerLoginResp::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nLoginResult, sizeof(nLoginResult))) return false;
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nIggId, sizeof(nIggId))) return false;
	return true;
}
